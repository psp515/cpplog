//
// Created by psp515 on 10.04.2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <format>
#include <memory>
#include <source_location>
#include <string>
#include <utility>
#include <vector>

#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>
#include <cpplog/common/log_level.h>
#include <cpplog/sink.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog {
    ///
    /// Logger class used to register events on various levels.
    ///
    class Logger {
    public:
        ///
        /// Creates logger with default log level mode.
        ///
        /// @param level Base level of registered events.
        /// @param options Formatted message options
        /// @param sinks
        explicit Logger(const LogLevel &level, const LogEventOptions &options,
                        vector<unique_ptr<Sink> > sinks)
            : sinks(move(sinks)), level(level), options(options) {
        }

        Logger() : level(DEBUG) {}

        Logger(Logger const &) = delete;

        Logger &operator=(Logger const &) = delete;

        ///
        /// Logs a message at DEBUG level.
        ///
        /// @param message The message to log.
        /// @param location The source location (defaults to current).
        void debug(const string &message, const source_location &location = source_location::current()) {
            this->log(DEBUG, message, location);
        }

        ///
        /// Logs a formatted message at DEBUG level.
        ///
        /// @param location The source location.
        /// @param fmt Format string.
        /// @param args Arguments for format string.
        template<typename... Args>
        void debug(const source_location &location, format_string<Args...> fmt, Args &&... args) {
            this->log(DEBUG, location, fmt, forward<Args>(args)...);
        }

        ///
        /// Logs a message at INFO level.
        ///
        /// @param message The message to log.
        /// @param location The source location (defaults to current).
        void info(const string &message, const source_location &location = source_location::current()) {
            this->log(INFO, message, location);
        }

        ///
        /// Logs a formatted message at INFO level.
        ///
        /// @param location The source location.
        /// @param fmt Format string.
        /// @param args Arguments for format string.
        template<typename... Args>
        void info(const source_location &location, format_string<Args...> fmt, Args &&... args) {
            this->log(INFO, location, fmt, forward<Args>(args)...);
        }

        ///
        /// Logs a message at WARNING level.
        ///
        /// @param message The message to log.
        /// @param location The source location (defaults to current).
        void warning(const string &message, const source_location &location = source_location::current()) {
            this->log(WARN, message, location);
        }

        ///
        /// Logs a formatted message at WARNING level.
        ///
        /// @param location The source location.
        /// @param fmt Format string.
        /// @param args Arguments for format string.
        template<typename... Args>
        void warning(const source_location &location, format_string<Args...> fmt, Args &&... args) {
            this->log(WARN, location, fmt, forward<Args>(args)...);
        }

        ///
        /// Logs a message at ERROR level.
        ///
        /// @param message The message to log.
        /// @param location The source location (defaults to current).
        void error(const string &message, const source_location &location = source_location::current()) {
            this->log(ERROR, message, location);
        }

        ///
        /// Logs a formatted message at ERROR level.
        ///
        /// @param location The source location.
        /// @param fmt Format string.
        /// @param args Arguments for format string.
        template<typename... Args>
        void error(const source_location &location, format_string<Args...> fmt, Args &&... args) {
            this->log(ERROR, location, fmt, forward<Args>(args)...);
        }

        ///
        /// Logs a message at CRITICAL level.
        ///
        /// @param message The message to log.
        /// @param location The source location (defaults to current).
        void critical(const string &message, const source_location &location = source_location::current()) {
            this->log(CRITICAL, message, location);
        }

        ///
        /// Logs a formatted message at CRITICAL level.
        ///
        /// @param location The source location.
        /// @param fmt Format string.
        /// @param args Arguments for format string.
        template<typename... Args>
        void critical(const source_location &location, format_string<Args...> fmt, Args &&... args) {
            this->log(CRITICAL, location, fmt, forward<Args>(args)...);
        }


        ///
        /// Sets log event options used in sinks for formatting message.
        ///
        /// @param options Object containing log format options.
        void setLogEventOptions(const LogEventOptions &options) {
            this->options = options;
        }

        ///
        /// Returns current options used in sinks for formatting message.
        ///
        /// @return Object containing log format options.
        [[nodiscard]] LogEventOptions getLogEventOptions() const {
            return this->options;
        }

    private:
        void log(const LogLevel level, const string &message, const source_location location) {
            const auto log_message = LogEvent(level, message, location);
            this->log(log_message);
        }

        template<class... Args>
        void log(const LogLevel level, const source_location &location,
                 const format_string<Args...> fmt, Args &&... args) {
            this->log(level, format(fmt, forward<Args>(args)...), location);
        }

        void log(const LogEvent &event) {
            if (level > event.getLevel())
                return;

            for (const auto &sink: this->sinks) {
                sink->log(options, event);
            }
        }

        vector<unique_ptr<Sink> > sinks;

        LogLevel level;

        LogEventOptions options;
    };
} // namespace cpplog

#endif // LOGGER_H
