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
    class Formatter
    {
    public:
        Formatter() = delete;

        explicit Formatter(const LogEventOptions& options) : options(options) {}

        [[nodiscard]] string format(const LogEvent& event) const;

    private:
        LogEventOptions options;
    };
}


#endif //TEXT_FORMATTER_H
