//
// Created by psp515 on 10.04.2025.
//

#ifndef SINK_H
#define SINK_H

#include <cpplog/common/log_level.h>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>

using namespace cpplog::common;

namespace cpplog {
    /// Base class representing sink. Sink should be secure for multithreading.
    class Sink {
    public:

        ///
        /// Disabled possibility to copy object.
        ///
        Sink(Sink const &) = delete;

        ///
        /// Disabled possibility to assign object.
        ///
        Sink &operator=(Sink const &) = delete;

        ///
        /// Disabled default ctor.
        ///
        Sink() = delete;

        ///
        /// Creates sink with specified base log level
        ///
        /// @param level Level for events to ignore.
        explicit Sink(const LogLevel level) : level(level) {
        }

        ///
        /// Function used to log event to specified sink. Function should be resistible to multithreading.
        ///
        /// @param event Event data.
        /// @param options Event format options.
        virtual void log(const LogEventOptions &options, const LogEvent &event) = 0;

        ///
        /// Virtual destructor for overloading.
        ///
        virtual ~Sink() = default;
    protected:
        LogLevel level = INFO;
    };
}

#endif //SINK_H
