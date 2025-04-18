//
// Created by kolbe on 10.04.2025.
//

#ifndef LOG_EVENT_H
#define LOG_EVENT_H

#include <cpplog/common/log_level.h>
#include <source_location>
#include <thread>
#include <chrono>
#include <utility>

using namespace std;

namespace cpplog::common
{
    ///
    /// Class represents single event in system with registered values.
    ///
    class LogEvent
    {
    public:
        ///
        /// Disabled creating events without values.
        LogEvent() = delete;

        ///
        /// Creates system event with source.
        ///
        /// @param level Level of event.
        /// @param message User message of event.
        /// @param source Source code of event.
        explicit LogEvent(const LogLevel& level, const string& message, const source_location& source) : LogEvent(level, message)
        {
            this->source = source;
            this->has_source = true;
        };

        ///
        /// Creates system event without source.
        ///
        /// @param level Level of event.
        /// @param message User message of event.
        explicit LogEvent(const LogLevel& level, string message) : level(level), message(std::move(message)), has_source(false)
        {
            this->thread = this_thread::get_id();
            this->timestamp = chrono::system_clock::to_time_t(chrono::system_clock::now());
        };

        ///
        /// Returns user message as string.
        ///
        /// @return User message.
        [[nodiscard]] string getMessage() const
        {
            return message;
        }

        ///
        /// Returns level of event.
        ///
        /// @return Level of event.
        [[nodiscard]] LogLevel getLevel() const
        {
            return level;
        }

        ///
        /// Returns thread id of registered event.
        ///
        /// @return Thread id.
        [[nodiscard]] thread::id getThread() const
        {
            return thread;
        }

        ///
        /// Returns function name that event occurred with specific code location.
        ///
        /// @return Function name with code location.
        [[nodiscard]] string getSourceFunctionName() const;

        ///
        /// Returns file name that event occurred.
        ///
        /// @return File name.
        [[nodiscard]] string getSourceFileName() const;

        ///
        /// Return time of registered event.
        ///
        /// @return Time in format "%Y-%m-%d %H:%M:%S"
        [[nodiscard]] string getTime() const;

    private:
        LogLevel level;

        thread::id thread;

        time_t timestamp;

        string message;

        bool has_source;
        source_location source;
    };
}

#endif //LOG_EVENT_H
