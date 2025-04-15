//
// Created by psp515 on 15.04.2025.
//

#include "formatter.h"

#include <sstream>
#include <cpplog/cpplog.h>

#include "formatter.h"

using namespace cpplog::extensions;

string Formatter::format(const LogEventOptions &options, const LogEvent &event) {
    ostringstream oss;

    if (options.logAsJson()) {
        oss << "{";
        oss << "\"time\": " << quoted(event.getTime()) << ",";
        oss << "\"level\": " << quoted(toString(event.getLevel())) << ",";

        if (options.logWithThread()) {
            oss << "\"thread\": " << event.getThread() << ",";
        }

        if (options.logWithSource()) {
            oss << "\"source_file\": " << quoted(event.getSourceFileName()) << ",";
            oss << "\"source_function\": " << quoted(event.getSourceFunctionName()) << ",";
        }

        oss << "\"message\": " << quoted(event.getMessage());
        oss << "}";
    } else {
        oss << "[" << event.getTime() << "]";
        oss << "[" << toString(event.getLevel()) << "]";

        if (options.logWithThread()) {
            oss << "[" << event.getThread() << "]";
        }

        if (options.logWithSource()) {
            oss << "[" << event.getSourceFileName() << "]";
            oss << "[" << event.getSourceFunctionName() << "]";
        }

        oss << "[" << event.getMessage() << "]";
    }

    return oss.str();
}
