//
// Created by kolbe on 18.04.2025.
//

#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

#include <string>
#include <cpplog/common/file_sink_options.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog::helpers {

    std::string readFileToEnd(const FileSinkOptions& options);

}



#endif //FILE_HELPERS_H
