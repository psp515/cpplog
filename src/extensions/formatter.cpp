//
// Created by psp515 on 15.04.2025.
//

#include "formatter.h"

#include <sstream>
#include <cpplog/cpplog.h>

#include "formatter.h"

using namespace cpplog::extensions;

string Formatter::format(const LogEvent &event) const
{
    ostringstream oss;

    if (this->options.logAsJson()) {
        oss << "{";
        oss << "\"time\": " << quoted(event.getTime()) << ",";
        oss << "\"level\": " << quoted(toString(event.getLevel())) << ",";

        if (this->options.logWithThread()) {
            oss << "\"thread\": " << event.getThread() << ",";
        }

        if (this->options.logWithSource()) {
            oss << "\"source_file\": " << quoted(event.getSourceFileName()) << ",";
            oss << "\"source_function\": " << quoted(event.getSourceFunctionName()) << ",";
        }

        oss << "\"message\": " << quoted(event.getMessage());
        oss << "}";
    } else {
        oss << "[" << event.getTime() << "]";
        oss << "[" << toString(event.getLevel()) << "]";

        if (this->options.logWithThread()) {
            oss << "[" << event.getThread() << "]";
        }

        if (this->options.logWithSource()) {
            oss << "[" << event.getSourceFileName() << "]";
            oss << "[" << event.getSourceFunctionName() << "]";
        }

        oss << " " << event.getMessage() << endl;
    }

    return oss.str();
}
