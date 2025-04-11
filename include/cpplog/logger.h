//
// Created by kolbe on 10.04.2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <memory>
#include <utility>
#include <source_location>
#include <string>
#include <format>


#include <cpplog/sink.h>
#include <cpplog/common/log_level.h>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog
{
    ///
    /// Logger class used to register events on various levels.
    ///
    class Logger
    {
    public:
        ///
        /// Creates logger with default log level mode.
        ///
        /// @param level Base level of registered events.
        /// @param options Formatted message options
        /// @param sinks
        explicit Logger(const LogLevel& level, const LogEventOptions& options,
                        vector<unique_ptr<Sink>> sinks) : sinks(move(sinks)), level(level), options(options)
        {
        }

        ///
        /// Creates empty logger.
        ///
        /// @param level Base level of registered events.
        explicit Logger(const LogLevel& level) : sinks(), level(level), options()
        {
        }

        Logger(Logger const&) = delete;
        Logger& operator=(Logger const&) = delete;
        ~Logger() = default;

    private:
        void log(LogEvent& event);

        vector<unique_ptr<Sink>> sinks;

        LogLevel level;

        LogEventOptions options;
    };
}

#endif //LOGGER_H
