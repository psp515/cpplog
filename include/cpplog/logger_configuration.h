//
// Created by psp515 on 15.04.2025.
//

#ifndef LOGGER_CONFIGURATION_H
#define LOGGER_CONFIGURATION_H

#include <memory>
#include <cpplog/common/log_event.h>
#include <cpplog/common/rotation_file_sink_options.h>
#include <cpplog/common/file_sink_options.h>
#include <cpplog/logger.h>
#include <cpplog/sink.h>


using namespace  std;

namespace cpplog {

    /// Class creates a logger instance or configures the default logger for use.
    class LoggerConfiguration final {
    public:

        ///
        /// Sets the base log level for the logger.
        ///
        /// @param level The minimum log level to allow messages through logger (you can override this level in concrete sink).
        /// @return Reference to this LoggerConfiguration for method chaining.
        ///
        LoggerConfiguration& setLoggerFilteringLevel(LogLevel level);

        ///
        /// Adds a custom sink to the logger's sink list.
        ///
        /// @param sink A unique pointer to a Sink instance that will handle log events.
        /// @return Reference to this LoggerConfiguration for method chaining.
        ///
        LoggerConfiguration& addSink(unique_ptr<Sink> sink);

        ///
        /// Adds a default standard output sink to the logger.
        ///
        /// @param level Override level for ignoring messages.
        /// @return Reference to this LoggerConfiguration for method chaining.
        ///
        LoggerConfiguration& addStdoutSink(LogLevel level = DEBUG);

        ///
        /// Adds a file sink to the logger.
        ///
        /// @param options Configuration options for file sink.
        /// @param level Override level for ignoring messages.
        /// @return Reference to this LoggerConfiguration for method chaining.
        ///
        LoggerConfiguration& addFileSink(const FileSinkOptions& options, LogLevel level = DEBUG);

        ///
        /// Adds a file sink with rotation to the logger.
        ///
        /// @param options Configuration options for file sink.
        /// @param level Override level for ignoring messages.
        /// @return Reference to this LoggerConfiguration for method chaining.
        ///
        LoggerConfiguration& addRotationFileSink(const RotationFileSinkOptions& options, LogLevel level = DEBUG);

        ///
        /// Applies this configuration to the global/default logger instance.
        /// Should be used when setting up a shared logger rather than building a new one.
        ///
        void configure();

        ///
        /// Builds and returns a new Logger instance using the configured settings.
        ///
        /// @return A unique pointer to a Logger with the current configuration.
        ///
        unique_ptr<Logger> build();

    private:
        vector<unique_ptr<Sink>> sinks;
        LogLevel level = INFO;
        LogEventOptions options;
    };


}

#endif //LOGGER_CONFIGURATION_H
