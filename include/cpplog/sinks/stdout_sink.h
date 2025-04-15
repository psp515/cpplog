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
    class StdoutSink final : public Sink {
    public:
        explicit StdoutSink(const LogLevel level) : Sink(level) { }

        void log(const LogEventOptions &options, const LogEvent &event) override;
    private:
        static mutex mtx;
    };
}

#endif //STDOUT_SINK_H
