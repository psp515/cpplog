//
// Created by kolbe on 18.04.2025.
//

#ifndef FILE_SINK_H
#define FILE_SINK_H

#include <mutex>
#include <cpplog/common/log_level.h>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>
#include <cpplog/common/file_sink_options.h>
#include <cpplog/sink.h>

namespace cpplog
{
    /// Sink saves messages to provided file in options.
    class FileSink final : public Sink
    {
    public:

        ///
        /// Creates sink with specified base log level
        ///
        /// @param level Level for events to ignore.
        /// @param options Options for saving logs.
        FileSink(const LogLevel& level, const FileSinkOptions& options);

        ///
        /// Function used to log event to specified sink.
        ///
        /// @param event Event data.
        /// @param options Event format options.
        void log(const LogEventOptions& options, const LogEvent& event) override;

    private:
        static mutex mtx;
        FileSinkOptions options;
        string log_file;
    };
}

#endif //FILE_SINK_H
