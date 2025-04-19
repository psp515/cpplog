//
// Created by psp515 on 18.04.2025.
//

#ifndef FILE_ROTATION_SINK_H
#define FILE_ROTATION_SINK_H

#include <cpplog/sink.h>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>
#include <cpplog/common/rotation_file_sink_options.h>

using namespace cpplog;
using namespace cpplog::common;

namespace cpplog::sinks
{
    /// Sink saves messages to provided file in options, but restricts maximal file size and number of historical files.
    class RotationFileSink final : public Sink
    {
    public:

        ///
        /// Creates rotation file sink with specified base log level and provided options.
        ///
        /// @param level Level for events to ignore.
        /// @param options Options for saving logs.
        RotationFileSink(const LogLevel& level, const RotationFileSinkOptions& options);

        ///
        /// Function used to log event to specified sink.
        ///
        /// @param event Event data.
        /// @param options Event format options.
        void log(const LogEventOptions& options, const LogEvent& event) override;

    private:
        string nextFileName() const;
        bool checkIfNeedsToRotate(size_t append_size) const;
        void rotateIfNecessary(size_t append_size);

        static mutex mtx;
        RotationFileSinkOptions options;
        string current_log_file;
    };
}

#endif //FILE_ROTATION_SINK_H
