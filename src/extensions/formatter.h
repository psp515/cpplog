//
// Created by psp515 on 15.04.2025.
//

#ifndef TEXT_FORMATTER_H
#define TEXT_FORMATTER_H

#include <string>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>

using namespace cpplog::common;

namespace cpplog::extensions
{
    /// Class created for formatting final message to log.
    class Formatter
    {
    public:
        /// Cannot create formatter without options.
        Formatter() = delete;

        ///
        /// Creates formatter object with options.
        ///
        /// @param options Options for formatting final log message.
        explicit Formatter(const LogEventOptions& options) : options(options) {}

        ///
        /// Method creates final message to log depending on options provided in constructor.
        /// Can create message as text or json.
        ///
        /// @param event Log event.
        /// @return Formatted message in json / text format depending on options.
        [[nodiscard]] string format(const LogEvent& event) const;

    private:
        LogEventOptions options;
    };
}


#endif //TEXT_FORMATTER_H
