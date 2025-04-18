//
// Created by psp515 on 15.04.2025.
//

#ifndef CPPLOG_H
#define CPPLOG_H

#include <cpplog/logger.h>
#include <memory>
#include <source_location>
#include <string>

using namespace std;

namespace cpplog {
    ///
    /// Static interface for globally accessible logging functionality.
    /// Encapsulates a singleton-like logger instance.
    ///
    class CppLog {
    public:

        ///
        /// Configures the global logger instance.
        ///
        /// @param logger A unique pointer to a fully configured Logger instance.
        ///
        static void configure(unique_ptr<Logger> logger) {
            instance = move(logger);
        }

        ///
        /// Logs a formatted DEBUG-level message.
        ///
        /// @tparam Args Format arguments.
        /// @param location Source location from which the log is emitted.
        /// @param fmt Format string.
        /// @param args Format arguments.
        ///
        template<class... Args>
        static void debug(const source_location &location, format_string<Args...> fmt, Args &&... args) {
            if (instance) {
                instance->debug(location, fmt, forward<Args>(args)...);
            }
        }

        ///
        /// Logs a plain DEBUG-level message.
        ///
        /// @param message The message string to log.
        /// @param location The source location (defaults to the caller).
        ///
        static void debug(const string &message,
                          const source_location &location = source_location::current()) {
            if (instance) {
                instance->debug(message, location);
            }
        }

        ///
        /// Logs a plain INFO-level message.
        ///
        /// @param message The message string to log.
        /// @param location The source location (defaults to the caller).
        ///
        static void info(const string &message,
                         const source_location &location = source_location::current()) {
            if (instance) {
                instance->info(message, location);
            }
        }

        ///
        /// Logs a formatted INFO-level message.
        ///
        /// @tparam Args Format arguments.
        /// @param location Source location from which the log is emitted.
        /// @param fmt Format string.
        /// @param args Format arguments.
        ///
        template<class... Args>
        static void info(const source_location &location, format_string<Args...> fmt, Args &&... args) {
            if (instance) {
                instance->info(location, fmt, forward<Args>(args)...);
            }
        }

        ///
        /// Logs a plain WARNING-level message.
        ///
        /// @param message The message string to log.
        /// @param location The source location (defaults to the caller).
        ///
        static void warning(const string &message,
                            const source_location &location = source_location::current()) {
            if (instance) {
                instance->warning(message, location);
            }
        }

        ///
        /// Logs a formatted WARNING-level message.
        ///
        /// @tparam Args Format arguments.
        /// @param location Source location from which the log is emitted.
        /// @param fmt Format string.
        /// @param args Format arguments.
        ///
        template<class... Args>
        static void warning(const source_location &location, format_string<Args...> fmt, Args &&... args) {
            if (instance) {
                instance->warning(location, fmt, forward<Args>(args)...);
            }
        }

        ///
        /// Logs a plain ERROR-level message.
        ///
        /// @param message The message string to log.
        /// @param location The source location (defaults to the caller).
        ///
        static void error(const string &message,
                          const source_location &location = source_location::current()) {
            if (instance) {
                instance->error(message, location);
            }
        }

        ///
        /// Logs a formatted ERROR-level message.
        ///
        /// @tparam Args Format arguments.
        /// @param location Source location from which the log is emitted.
        /// @param fmt Format string.
        /// @param args Format arguments.
        ///
        template<class... Args>
        static void error(const source_location &location, format_string<Args...> fmt, Args &&... args) {
            if (instance) {
                instance->error(location, fmt, forward<Args>(args)...);
            }
        }

        ///
        /// Logs a plain CRITICAL-level message.
        ///
        /// @param message The message string to log.
        /// @param location The source location (defaults to the caller).
        ///
        static void critical(const string &message,
                             const source_location &location = source_location::current()) {
            if (instance) {
                instance->critical(message, location);
            }
        }

        ///
        /// Logs a formatted CRITICAL-level message.
        ///
        /// @tparam Args Format arguments.
        /// @param location Source location from which the log is emitted.
        /// @param fmt Format string.
        /// @param args Format arguments.
        ///
        template<class... Args>
        static void critical(const source_location &location, format_string<Args...> fmt, Args &&... args) {
            if (instance) {
                instance->critical(location, fmt, forward<Args>(args)...);
            }
        }

        ///
        /// Sets log event options used in sinks for formatting message.
        ///
        /// @param options Object containing log format options.
        static void setLogEventOptions(const LogEventOptions &options) {
            instance->setLogEventOptions(options);
        }

    private:
        static unique_ptr<Logger> instance;
    };
}

#endif //CPPLOG_H
