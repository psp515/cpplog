//
// Created by kolbe on 18.04.2025.
//

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <gtest/gtest.h>
#include <cpplog/logger.h>
#include <cpplog/cpplog.h>
#include <cpplog/logger_configuration.h>

#include "../helpers/file_helpers.h"

using namespace std;
using namespace cpplog;
using namespace cpplog::helpers;


TEST(FileSinkTests, LogsMessages) {
    // Arrange
    const string expectedMessage = "Debug message";
    const FileSinkOptions options;

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addFileSink(options)
        .configure();

    // Act
    CppLog::info(expectedMessage);
    const auto output = readFileToEnd(options);

    // Assert
    EXPECT_TRUE(output.find("[") != string::npos);
    EXPECT_EQ(count(output.begin(), output.end(), '['), 2);
    EXPECT_TRUE(output.find("FilteringWorks") == string::npos);
    EXPECT_TRUE(output.find("stdout_sink_tests.cpp") == string::npos);
}

TEST(FileSinkTests, SinkFilteringWorks) {
    // Arrange
    const string expectedMessage = "Filtering message";
    const FileSinkOptions options;

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addFileSink(options, WARN)
        .configure();

    // Act
    CppLog::info(expectedMessage);
    const auto output = readFileToEnd(options);

    // Assert
    EXPECT_TRUE(output.find("[") == string::npos);
    EXPECT_TRUE(output.find("SinkFilteringWorks") == string::npos);
    EXPECT_TRUE(output.find("stdout_sink_tests.cpp") == string::npos);
}

TEST(FileSinkTests, OverrideOptionsWorks) {
    // Arrange
    const string expectedMessage = "Debug message";
    const FileSinkOptions options;

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addFileSink(options)
        .configure();

    // Act
    CppLog::setLogEventOptions(LogEventOptions(false, false, true));
    CppLog::info(expectedMessage);
    const auto output = readFileToEnd(options);

    // Assert
    EXPECT_TRUE(output.find("[") != string::npos);
    EXPECT_EQ(count(output.begin(), output.end(), '['), 4);
    EXPECT_TRUE(output.find("OverrideOptionsWorks") != string::npos);
    EXPECT_TRUE(output.find("file_sink_tests.cpp") != string::npos);
}

TEST(FileSinkTests, LogAsJson) {
    // Arrange
    const string expectedMessage = "Debug message";
    const FileSinkOptions options;

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addFileSink(options)
        .configure();

    // Act
    CppLog::setLogEventOptions(LogEventOptions(true, false, true));
    CppLog::info(expectedMessage);
    const auto output = readFileToEnd(options);

    // Assert
    EXPECT_TRUE(output.find("LogAsJson") != string::npos);
    EXPECT_TRUE(output.find("file_sink_tests.cpp") != string::npos);
    EXPECT_TRUE(output.find("\"message\":") != string::npos);
    EXPECT_TRUE(output.find("\"source_file\":") != string::npos);
    EXPECT_TRUE(output.find("\"source_function\":") != string::npos);
    EXPECT_TRUE(output.find("\"time\":") != string::npos);
    EXPECT_TRUE(output.find("\"level\":") != string::npos);
}

TEST(FileSinkTests, CleansFileOnInitialize) {
    // Arrange
    const string notExpectedMessage = "Debug message - cleared";
    const string expectedMessage = "Debug message 2";
    const FileSinkOptions options;

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addFileSink(options)
        .configure();

    // Act
    CppLog::info(notExpectedMessage);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addFileSink(options)
        .configure();

    CppLog::info(expectedMessage);

    const auto output = readFileToEnd(options);

    // Assert
    EXPECT_TRUE(output.find(expectedMessage) != string::npos);
    EXPECT_TRUE(output.find(notExpectedMessage) == string::npos);
}

TEST(FileSinkTests, DoesNotCleanOnInitialize) {
    // Arrange
    const string expectedMessage1 = "Debug message";
    const string expectedMessage2 = "Debug message 2";
    const FileSinkOptions options1;
    const FileSinkOptions options2 = FileSinkOptions("logs.txt", "logs", false);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addFileSink(options1)
        .configure();

    // Act
    CppLog::info(expectedMessage1);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addFileSink(options2)
        .configure();

    CppLog::info(expectedMessage2);

    const auto output = readFileToEnd(options1);

    // Assert
    EXPECT_TRUE(output.find(expectedMessage1) != string::npos);
    EXPECT_TRUE(output.find(expectedMessage2) != string::npos);
}