//
// Created by psp515 on 18.04.2025.
//

#include <mutex>
#include <utility>
#include <filesystem>
#include <fstream>
#include <cpplog/sinks/file_sink.h>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>
#include <cpplog/common/log_level.h>

#include "../src/extensions/formatter.h"

using namespace std;
using namespace cpplog;
using namespace cpplog::common;
using namespace cpplog::extensions;

mutex FileSink::mtx;

FileSink::FileSink(const LogLevel& level, const FileSinkOptions& options) : Sink(level), options(options)
{
    // Dir exists

    const filesystem::path dir(options.folderName());

    if(!is_directory(dir)) {
        create_directory(dir);
    }

    // File exists

    const filesystem::path file(options.baseFileName());
    const filesystem::path full_path = dir / file;

    auto mode = options.cleanOnInitialize() ? ios::out | ios::trunc : ios::app;

    ofstream ofs(full_path, mode);
    ofs.close();

    this->log_file = move(full_path.string());
}

void FileSink::log(const LogEventOptions& options, const LogEvent& event)
{
    if (event.getLevel() < this->level)
        return;

    const auto formatter = Formatter(options);

    lock_guard lock{mtx};

    ofstream file(this->log_file, ios_base::app);

    file << formatter.format(event) << endl;

    file.close();
}