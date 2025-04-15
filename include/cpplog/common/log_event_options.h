//
// Created by kolbe on 10.04.2025.
//

#ifndef LOGGER_OPTIONS_H
#define LOGGER_OPTIONS_H

namespace cpplog::common
{
    ///
    /// Options possible to adjust for output formatted message.
    ///
    class LogEventOptions
    {
    public:
        ///
        /// Creates log event options object.
        ///
        /// @param json Tells if output event message should be json.
        /// @param thread Tells if output event message should have thread id.
        /// @param source Tells if output event message should have source code information.
        explicit  LogEventOptions(const bool json, const bool thread, const bool source) : json(json), thread(thread),
                                                                                 source(source)
        {
        }

        ///
        /// Creates base event options.
        ///
        LogEventOptions() = default;

        ///
        /// Tells if message should be logged as json.
        ///
        /// @return
        [[nodiscard]] bool logAsJson() const
        {
            return json;
        }

        ///
        /// Tells if formatted message should be logged with thread information
        ///
        /// @return
        [[nodiscard]] bool logWithThread() const
        {
            return thread;
        }

        ///
        /// Tells if formatted message should be logged with source.
        ///
        /// @return
        [[nodiscard]] bool logWithSource() const
        {
            return source;
        }

    private:
        bool json = false;
        bool thread = false;
        bool source = false;
    };
}

#endif //LOGGER_OPTIONS_H
