//
// Created by psp515 on 10.04.2025.
//

#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

#include <string>

#undef DEBUG
#undef INFO
#undef WARN
#undef ERROR
#undef CRITICAL

using namespace std;

namespace cpplog::common {

    ///
    /// Enum represents possible to register error levels.
    ///
    enum LogLevel {
        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3,
        CRITICAL = 4
    };

    ///
    /// Converts LogLevel enum to a human-readable string.
    ///
    inline string toString(const LogLevel level) {
        switch (level) {
            case DEBUG: return "DEBUG";
            case INFO: return "INFO";
            case WARN: return "WARN";
            case ERROR: return "ERROR";
            case CRITICAL: return "CRITICAL";
            default: return "UNKNOWN";
        }
    }
}


#endif //LOG_LEVEL_H
