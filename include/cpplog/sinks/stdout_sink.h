//
// Created by psp515 on 15.04.2025.
//

#ifndef STDOUT_SINK_H
#define STDOUT_SINK_H

#include <mutex>
#include <cpplog/sink.h>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>
#include <cpplog/common//log_level.h>

using namespace std;
using namespace cpplog;
using namespace cpplog::common;

namespace cpplog::sinks {

    /// Sinks sends filtered messages to std::cout.
    class StdoutSink final : public Sink {
    public:
        ///
        /// Creates sink with specified base log level
        ///
        /// @param level Level for events to ignore.
        explicit StdoutSink(const LogLevel level) : Sink(level) { }

        ///
        /// Function used to log event to specified sink.
        ///
        /// @param event Event data.
        /// @param options Event format options.
        void log(const LogEventOptions &options, const LogEvent &event) override;
    private:
        static mutex mtx;
    };
}

#endif //STDOUT_SINK_H
