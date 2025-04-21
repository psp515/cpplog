//
// Created by psp515 on 19.04.2025.
//

#ifndef SIMPLE_HTTP_SINK_H
#define SIMPLE_HTTP_SINK_H

#include <cpplog/sink.h>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>
#include <winsock2.h>

#include "win_http_sink_options.h"


class WinHttpSink final : public cpplog::Sink
{
public:
    ///
    /// Creates sink with specified base log level
    ///
    /// @param level Level for events to ignore.
    /// @param options Options for HttpSInk
    explicit WinHttpSink(LogLevel level, const WinHttpSinkOptions& options);

    ///
    /// Function used to log event to specified sink.
    ///
    /// @param event Event data.
    /// @param options Event format options.
    void log(const LogEventOptions &options, const LogEvent &event) override;

    ///
    /// Destructor for ensuring proper freeing winsock.
    ///
    ~WinHttpSink() override;

private:
    string getRequest(const LogEventOptions &options, const LogEvent &event) const;
    WinHttpSinkOptions options;
    WSADATA wsaData;

};


#endif //SIMPLE_HTTP_SINK_H
