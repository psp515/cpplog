//
// Created by psp515 on 15.04.2025.
//

#ifndef TEXT_FORMATTER_H
#define TEXT_FORMATTER_H

#include <string>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>

using namespace cpplog::common;

namespace cpplog::extensions {
    class Formatter {
        public:
            static string format(const LogEventOptions &options, const LogEvent &event);
    };
}



#endif //TEXT_FORMATTER_H
