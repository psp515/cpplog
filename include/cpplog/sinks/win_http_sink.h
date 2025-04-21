//
// Created by kolbe on 19.04.2025.
//

#ifndef SIMPLE_HTTP_SINK_H
#define SIMPLE_HTTP_SINK_H

#include <cpplog/sink.h>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>

namespace cpplog::sink
{
    class SimpleHttpSink final : public Sink
    {
    public:
        ///
        /// Creates sink with specified base log level
        ///
        /// @param level Level for events to ignore.
        explicit SimpleHttpSink(const LogLevel level) : Sink(level) { }

        ///
        /// Function used to log event to specified sink.
        ///
        /// @param event Event data.
        /// @param options Event format options.
        void log(const LogEventOptions &options, const LogEvent &event) override;

    };
}

#endif //SIMPLE_HTTP_SINK_H
