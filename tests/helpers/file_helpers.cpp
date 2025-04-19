//
// Created by psp515 on 18.04.2025.
//

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cpplog/common/file_sink_options.h>
#include <cpplog/common/rotation_file_sink_options.h>

#include "file_helpers.h"

#include <algorithm>
#include <vector>

using namespace std;
using namespace cpplog::common;

string cpplog::helpers::readFileToEnd(const FileSinkOptions& options)
{
    filesystem::path full_path = filesystem::path(options.folderName()) / options.baseFileName();

    ifstream file(full_path);
    if (!file.is_open())
    {
        throw runtime_error("Could not open file: " + full_path.string());
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


string cpplog::helpers::rotationReadFileToEnd(const RotationFileSinkOptions& options)
{
    const filesystem::path dir = options.folderName();
    const string baseName = filesystem::path(options.baseFileName()).stem().string();
    const string extension = filesystem::path(options.baseFileName()).extension().string();

    vector<filesystem::directory_entry> matchingFiles;

    for (const auto& entry : filesystem::directory_iterator(dir))
    {
        const string filename = entry.path().filename().string();
        if (filename.starts_with(baseName + "_") && filename.ends_with(extension))
        {
            matchingFiles.push_back(entry);
        }
    }

    if (matchingFiles.empty())
    {
        throw runtime_error("No matching log files found in directory: " + dir.string());
    }

    sort(matchingFiles.begin(), matchingFiles.end(),
              [](const filesystem::directory_entry& a, const filesystem::directory_entry& b)
              {
                  return a.path().filename().string() < b.path().filename().string();
              });

    const filesystem::path firstFile = matchingFiles.front().path();

    ifstream file(firstFile);
    if (!file.is_open())
    {
        throw runtime_error("Could not open file: " + firstFile.string());
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

size_t cpplog::helpers::countFilesWithBaseName(const RotationFileSinkOptions& options)
{
    const filesystem::path dir = options.folderName();
    const string baseName = filesystem::path(options.baseFileName()).stem().string();
    const string extension = filesystem::path(options.baseFileName()).extension().string();

    size_t count = 0;

    for (const auto& entry : filesystem::directory_iterator(dir))
    {
        const string filename = entry.path().filename().string();
        if (filename.starts_with(baseName + "_") && filename.ends_with(extension))
        {
            count++;
        }
    }

    return count;
}
