//
// Created by psp515 on 18.04.2025.
//

#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

#include <string>
#include <cpplog/common/file_sink_options.h>
#include <cpplog/common/rotation_file_sink_options.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog::helpers {

    string readFileToEnd(const FileSinkOptions& options);

    string rotationReadFileToEnd(const RotationFileSinkOptions& options);

    size_t countFilesWithBaseName(const RotationFileSinkOptions& options);
}



#endif //FILE_HELPERS_H
