//
// Created by psp515 on 19.04.2025.
//

#include <chrono>
#include <iomanip>
#include <sstream>
#include <random>
#include <mutex>
#include <utility>
#include <filesystem>
#include <fstream>
#include <cpplog/sinks/rotation_file_sink.h>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>
#include <cpplog/common/rotation_file_sink_options.h>

#include "../extensions/formatter.h"

using namespace cpplog::sinks;
using namespace cpplog::common;
using namespace cpplog::extensions;

mutex RotationFileSink::mtx;

RotationFileSink::RotationFileSink(const LogLevel& level, const RotationFileSinkOptions& options) : Sink(level),
    options(options)
{
    // Dir exists

    const filesystem::path dir(options.folderName());

    if (!is_directory(dir))
    {
        create_directory(dir);
    }

    // Clean dir

    if (options.cleanOnInitialize())
    {

        const auto base = filesystem::path(options.baseFileName()).stem().string();
        for (const auto& entry : filesystem::directory_iterator(dir))
        {
            const auto& path = entry.path();

            if (path.filename().string().starts_with(base))
            {
                filesystem::remove(path);
            }
        }
    }

    // File exists

    const auto full_path = nextFileName();

    auto mode = options.cleanOnInitialize() ? ios::out | ios::trunc : ios::app;

    ofstream ofs(full_path, mode);
    ofs.close();

    this->current_log_file = move(full_path);
}


bool RotationFileSink::checkIfNeedsToRotate(const size_t append_size) const
{
    if (!filesystem::exists(this->current_log_file))
        return true;

    const auto fileSizeInBytes = filesystem::file_size(this->current_log_file);
    const auto maxSizeInBytes = options.getMaximalFileSizeKiloBytes() * 1024;

    if (fileSizeInBytes + append_size < maxSizeInBytes)
        return false;

    return true;
}

void RotationFileSink::rotateIfNecessary(const size_t append_size)
{
    if (!this->checkIfNeedsToRotate(append_size))
        return;

    const auto dir = filesystem::path(options.folderName());
    const auto base = filesystem::path(options.baseFileName()).stem().string();
    const auto ext = filesystem::path(options.baseFileName()).extension().string();

    const auto nextFileName = this->nextFileName();

    // Find matching log files
    vector<filesystem::directory_entry> matchingFiles;
    for (const auto& entry : filesystem::directory_iterator(dir))
    {
        const string fname = entry.path().filename().string();
        if (fname.starts_with(base + "_") && fname.ends_with(ext))
        {
            matchingFiles.push_back(entry);
        }
    }

    // Sort Files
    sort(matchingFiles.begin(), matchingFiles.end(),
              [](const filesystem::directory_entry& a, const filesystem::directory_entry& b)
              {
                  return filesystem::last_write_time(a) < filesystem::last_write_time(b);
              });

    // Remove old files
    const size_t maxHistory = options.getNumberOfHistoricalFiles();
    if (matchingFiles.size() >= maxHistory)
    {
        size_t numToRemove = matchingFiles.size() - maxHistory;
        for (size_t i = 0; i < numToRemove; i++)
        {
            filesystem::remove(matchingFiles[i]);
        }
    }

    current_log_file = nextFileName;
}

void RotationFileSink::log(const LogEventOptions& options, const LogEvent& event)
{
    if (event.getLevel() < this->level)
        return;

    lock_guard lock{mtx};

    const auto formatter = Formatter(options);
    const auto message = formatter.format(event);

    const auto max_file_size = this->options.getMaximalFileSizeKiloBytes() * 1024;

    if (max_file_size < message.size())
    {
        throw runtime_error(
            "Log entry too large to fit in a single file. Consider increasing the maximum file size.");
    }

    rotateIfNecessary(message.size());

    ofstream file(this->current_log_file, ios_base::app);

    file << message << endl;

    file.close();
}

string RotationFileSink::nextFileName() const
{
    const filesystem::path basePath(options.baseFileName());
    const string stem = basePath.stem().string();
    const string extension = basePath.extension().string();

    const auto now = chrono::system_clock::now();
    const auto ns_since_epoch = chrono::duration_cast<chrono::nanoseconds>(
        now.time_since_epoch()).count();

    thread_local mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(1, 9999);
    const int randomSuffix = dist(rng);

    ostringstream fileNameStream;
    fileNameStream << stem << "_" << ns_since_epoch << "_" << randomSuffix << extension;

    const filesystem::path fullPath = filesystem::path(options.folderName()) / fileNameStream.str();

    return fullPath.string();
}
