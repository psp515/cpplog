//
// Created by kolbe on 18.04.2025.
//


#include <gtest/gtest.h>
#include <cpplog/logger.h>
#include <cpplog/cpplog.h>
#include <cpplog/logger_configuration.h>

#include "mocks/mock_sink.h"

using namespace cpplog;
using namespace cpplog::mocks;

TEST(CppLogTest, LogsMessageAtLevel) {
    // Arrange
    const string expectedMessage = "Debug message";
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

TEST(CppLogTest, DoesNotLogBelowConfiguredLevel) {
    // Arrange
    const string expectedMessage = "Debug message";
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(WARN, logs);
    LoggerConfiguration()
        .setLoggerFilteringLevel(WARN)
        .addSink(std::move(mockSink))
        .configure();

    // Act
    CppLog::info("This should not be logged");

    // Assert
    EXPECT_TRUE(logs->empty());
}

TEST(CppLogTest, LogsWithSourceLocation) {
    // Arrange
    const std::string msg = "Log with explicit location";
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(INFO, logs);
    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addSink(std::move(mockSink))
        .configure();

    // Act
    CppLog::info(msg);

    // Assert
    ASSERT_EQ(logs->size(), 1);

    const auto& event = get<LogEvent>(logs->at(0));
    EXPECT_EQ(event.getMessage(), msg);
    EXPECT_TRUE(event.getSourceFunctionName().find("LogsWithSourceLocation"));
    EXPECT_TRUE(event.getSourceFileName().find("logger_tests.cpp"));
}

TEST(CppLogTest, TemplateLogsWithSourceLocation) {
    // Arrange
    const std::string msg = "Log with explicit location 1";
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(WARN, logs);
    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addSink(std::move(mockSink))
        .configure();

    // Act
    CppLog::warning(source_location::current(), "Log with explicit location {0}", 1);

    // Assert
    ASSERT_EQ(logs->size(), 1);

    const auto& event = get<LogEvent>(logs->at(0));
    EXPECT_EQ(event.getMessage(), msg);
    EXPECT_TRUE(event.getSourceFunctionName().find("LogsWithSourceLocation"));
    EXPECT_TRUE(event.getSourceFileName().find("logger_tests.cpp"));
}