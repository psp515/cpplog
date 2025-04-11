//
// Created by kolbe on 10.04.2025.
//

#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

namespace cpplog::common
{
    ///
    /// Enum represents possible to register error levels.
    ///
    enum LogLevel
    {
        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3,
        CRITICAL = 4
    };
}


#endif //LOG_LEVEL_H
