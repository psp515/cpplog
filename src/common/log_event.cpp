//
// Created by kolbe on 10.04.2025.
//

#include <iomanip>
#include <ctime>
#include <sstream>
#include <cpplog/common/log_event.h>

using namespace std;
using namespace cpplog::common;

string LogEvent::getSourceFunctionName() const{
    if (!this->has_source)
        return "Unknown";

    return source.function_name();
}

string LogEvent::getSourceFileName() const{
    if (!this->has_source)
        return "Unknown";

    ostringstream oss;

    oss << this->source.file_name()
        << '('
        << this->source.line()
        << ':'
        << this->source.column()
        << ')';

    return oss.str();
}

string LogEvent::getTime() const {
    ostringstream oss;
    oss << put_time(localtime(&this->timestamp), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}