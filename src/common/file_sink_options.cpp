//
// Created by kolbe on 21.04.2025.
//

#include <stdexcept>
#include <cpplog/common/file_sink_options.h>

using namespace cpplog::common;

FileSinkOptions::FileSinkOptions() : log_file_name("logs.txt"), log_folder_name("logs"), clean(true)
{
    this->FileSinkOptions::validate();
}

FileSinkOptions::FileSinkOptions(const string& file_name, const string& folder_name, const bool clean_on_initialize)
            : log_file_name(file_name), log_folder_name(folder_name), clean(clean_on_initialize)
{
    this->FileSinkOptions::validate();
}

void FileSinkOptions::validate()
{
    if (log_file_name.empty())
        throw invalid_argument("Log file name cannot be empty.");

    if (log_folder_name.empty())
        throw invalid_argument("Log folder name cannot be empty.");
}