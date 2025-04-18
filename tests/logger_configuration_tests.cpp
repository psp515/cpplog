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

#include "helpers/file_helpers.h"
#include "helpers/mock_sink.h"

using namespace std;
using namespace cpplog;
using namespace cpplog::helpers;

TEST(LoggerConfigurationTests, StdoutSinkWorks) {
    // Arrange
    const string expectedMessage = "Stdout message";

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addStdoutSink()
        .configure();

    // Act
    streambuf* orig_buf = cout.rdbuf();
    stringstream buffer;
    cout.rdbuf(buffer.rdbuf());
    CppLog::info(expectedMessage);
    cout.rdbuf(orig_buf);
    auto output = buffer.str();

    // Assert
    EXPECT_TRUE(output.find("[") != string::npos);
    EXPECT_EQ(count(output.begin(), output.end(), '['), 2);
    EXPECT_TRUE(output.find("FilteringWorks") == string::npos);
    EXPECT_TRUE(output.find("stdout_sink_tests.cpp") == string::npos);
}

TEST(LoggerConfigurationTests, FileSinkWorks) {
    // Arrange
    const string expectedMessage = "File message";
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

TEST(LoggerConfigurationTests, AddsCustomSink) {
    // Arrange
    const string expectedMessage = "Mock message";
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(INFO, logs);
    LoggerConfiguration()
      .setLoggerFilteringLevel(INFO)
      .addSink(std::move(mockSink))
      .configure();

    // Act
    CppLog::info(expectedMessage);

    // Assert
    ASSERT_EQ(logs->size(), 1);
    const auto& log = logs->at(0);
    const auto& event = get<LogEvent>(log);
    EXPECT_EQ(event.getLevel(), INFO);
    EXPECT_EQ(event.getMessage(), expectedMessage);
}

TEST(LoggerConfigurationTests, ConfiguresMultipleSinks) {
    // Arrange
    const string expectedMessage = "Multi message";
    const FileSinkOptions options;

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addStdoutSink()
        .addFileSink(options)
        .configure();

    // Act
    streambuf* orig_buf = cout.rdbuf();
    stringstream buffer;
    cout.rdbuf(buffer.rdbuf());
    CppLog::info(expectedMessage);
    cout.rdbuf(orig_buf);
    auto stdout_output = buffer.str();

    auto file_output = readFileToEnd(options);

    // Assert
    EXPECT_TRUE(stdout_output.find("[") != string::npos);
    EXPECT_EQ(count(stdout_output.begin(), stdout_output.end(), '['), 2);
    EXPECT_TRUE(stdout_output.find("FilteringWorks") == string::npos);
    EXPECT_TRUE(stdout_output.find("stdout_sink_tests.cpp") == string::npos);

    EXPECT_TRUE(file_output.find("[") != string::npos);
    EXPECT_EQ(count(file_output.begin(), file_output.end(), '['), 2);
    EXPECT_TRUE(file_output.find("FilteringWorks") == string::npos);
    EXPECT_TRUE(file_output.find("stdout_sink_tests.cpp") == string::npos);
}

TEST(LoggerConfigurationTests, SetsDefaultFilteringLevel) {
    // Arrange
    const string expectedMessage = "Mock message";
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(INFO, logs);
    LoggerConfiguration()
      .setLoggerFilteringLevel(CRITICAL)
      .addSink(std::move(mockSink))
      .configure();

    // Act
    CppLog::debug(expectedMessage);
    CppLog::info(expectedMessage);
    CppLog::warning(expectedMessage);
    CppLog::error(expectedMessage);
    CppLog::critical(expectedMessage);

    // Assert
    ASSERT_EQ(logs->size(), 1);
    const auto& log = logs->at(0);
    const auto& event = get<LogEvent>(log);
    EXPECT_EQ(event.getLevel(), CRITICAL);
    EXPECT_EQ(event.getMessage(), expectedMessage);
}