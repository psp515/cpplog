//
// Created by kolbe on 18.04.2025.
//

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <cpplog/common/file_sink_options.h>

#include "file_helpers.h"

using namespace std;
using namespace cpplog::common;

string cpplog::helpers::readFileToEnd(const FileSinkOptions& options) {
    filesystem::path full_path = std::filesystem::path(options.folderName()) / options.baseFileName();

    ifstream file(full_path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + full_path.string());
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}