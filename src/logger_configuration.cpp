//
// Created by psp515 on 15.04.2025.
//

#include <memory>

#include <cpplog/cpplog.h>
#include <cpplog/logger_configuration.h>
#include <cpplog/sinks/stdout_sink.h>
#include <cpplog/sinks/file_sink.h>
#include <cpplog/common/file_sink_options.h>

using namespace cpplog;
using namespace cpplog::sinks;

unique_ptr<Logger> LoggerConfiguration::build() {
    if(!sinks.empty()) {
        return make_unique<Logger>(level, options, move(sinks));
    }

    return make_unique<Logger>();
}

void LoggerConfiguration::configure() {
    auto logger = build();

    CppLog::configure(move(logger));
}

LoggerConfiguration& LoggerConfiguration::setLoggerFilteringLevel(const LogLevel level) {
    this->level = level;
    return *this;
}

LoggerConfiguration &LoggerConfiguration::addSink(unique_ptr<Sink> sink) {
    sinks.push_back(move(sink));
    return *this;
}

LoggerConfiguration &LoggerConfiguration::addStdoutSink(LogLevel level) {
    sinks.push_back(make_unique<StdoutSink>(level));
    return *this;
}

LoggerConfiguration &LoggerConfiguration::addFileSink(FileSinkOptions options, LogLevel level)
{
    sinks.push_back(make_unique<FileSink>(level, move(options)));
    return *this;
}
