//
// Created by psp515 on 15.04.2025.
//

#include <memory>
#include <gtest/gtest.h>
#include <cpplog/logger.h>
#include <cpplog/logger_configuration.h>
#include <cpplog/common/log_level.h>
#include <source_location>

#include "helpers/mock_sink.h"

using namespace std;
using namespace cpplog;
using namespace cpplog::helpers;
using namespace cpplog::common;

TEST(LoggerTest, CanLogAllLevels)
{
    // Arrange
    const string expectedMessage = "Debug message";
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(DEBUG, logs);
    const auto logger = LoggerConfiguration()
                  .setLoggerFilteringLevel(DEBUG)
                  .addSink(move(mockSink))
                  .build();

    // Act
    logger->debug(expectedMessage);
    logger->info(expectedMessage);
    logger->warning(expectedMessage);
    logger->error(expectedMessage);
    logger->critical(expectedMessage);

    // Assert
    ASSERT_EQ(logs->size(), 5);
}

TEST(LoggerTest, TemplateCanLogAllLevels)
{
    // Arrange
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(DEBUG, logs);
    auto logger = LoggerConfiguration()
                  .setLoggerFilteringLevel(DEBUG)
                  .addSink(move(mockSink))
                  .build();

    // Act
    logger->debug(source_location::current(),"Debug message {0}", 345);
    logger->info(source_location::current(),"Debug message {0}", false);
    logger->warning(source_location::current(),"Debug message {0}", "sdfsd");
    logger->error(source_location::current(),"Debug message {0}", -1);
    logger->critical(source_location::current(),"Debug message {0}", 0.01);

    // Assert
    ASSERT_EQ(logs->size(), 5);
}

TEST(LoggerTest, LogsMessageAtLevel)
{
    // Arrange
    const string expectedMessage = "Debug message";
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(INFO, logs);
    auto logger = LoggerConfiguration()
                  .setLoggerFilteringLevel(INFO)
                  .addSink(move(mockSink))
                  .build();

    // Act
    logger->info(expectedMessage);

    // Assert
    ASSERT_EQ(logs->size(), 1);
    const auto& log = logs->at(0);
    const auto& event = get<LogEvent>(log);
    EXPECT_EQ(event.getLevel(), INFO);
    EXPECT_EQ(event.getMessage(), expectedMessage);
}

TEST(LoggerTest, DoesNotLogBelowConfiguredLevel)
{
    // Arrange
    const string expectedMessage = "Debug message";
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(WARN, logs);
    auto logger = LoggerConfiguration()
                  .setLoggerFilteringLevel(WARN)
                  .addSink(move(mockSink))
                  .build();

    // Act
    logger->info("This should not be logged");

    // Assert
    EXPECT_TRUE(logs->empty());
}

TEST(LoggerTest, LogsWithSourceLocation)
{
    // Arrange
    const string msg = "Log with explicit location";
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(INFO, logs);
    auto logger = LoggerConfiguration()
                  .setLoggerFilteringLevel(INFO)
                  .addSink(move(mockSink))
                  .build();

    // Act
    logger->info(msg);

    // Assert
    ASSERT_EQ(logs->size(), 1);

    const auto& event = get<LogEvent>(logs->at(0));
    EXPECT_EQ(event.getMessage(), msg);
    EXPECT_TRUE(event.getSourceFunctionName().find("LogsWithSourceLocation"));
    EXPECT_TRUE(event.getSourceFileName().find("logger_tests.cpp"));
}

TEST(LoggerTest, TemplateLogsWithSourceLocation)
{
    // Arrange
    const string msg = "Log with explicit location 1";
    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(WARN, logs);
    auto logger = LoggerConfiguration()
                  .setLoggerFilteringLevel(WARN)
                  .addSink(move(mockSink))
                  .build();

    // Act
    logger->warning(source_location::current(), "Log with explicit location {0}", 1);

    // Assert
    ASSERT_EQ(logs->size(), 1);

    const auto& event = get<LogEvent>(logs->at(0));
    EXPECT_EQ(event.getMessage(), msg);
    EXPECT_TRUE(event.getSourceFunctionName().find("LogsWithSourceLocation"));
    EXPECT_TRUE(event.getSourceFileName().find("logger_tests.cpp"));
}

TEST(LoggerTest, CorrectOptionsPass)
{
    // Arrange
    const string expectedMessage1 = "Value: 42";
    const string expectedMessage2 = "Value: 41";

    auto logs = make_shared<vector<pair<LogEvent, LogEventOptions>>>();
    auto mockSink = make_unique<MockSink>(WARN, logs);
    auto logger = LoggerConfiguration()
                  .setLoggerFilteringLevel(WARN)
                  .addSink(move(mockSink))
                  .build();

    // Act
    logger->warning(source_location::current(), "Value: {}", 42);
    logger->setLogEventOptions(LogEventOptions(false, true, true));
    logger->error(source_location::current(), "Value: {}", 41);

    // Assert
    ASSERT_EQ(logs->size(), 2);

    const auto& event1 = get<0>(logs->at(0));
    EXPECT_EQ(event1.getLevel(), WARN);
    EXPECT_EQ(event1.getMessage(), expectedMessage1);
    const auto& options1 = get<1>(logs->at(0));
    EXPECT_EQ(options1.logWithThread(), false);
    EXPECT_EQ(options1.logAsJson(), false);
    EXPECT_EQ(options1.logWithSource(), false);

    const auto& event2 = get<0>(logs->at(1));
    EXPECT_EQ(event2.getLevel(), ERROR);
    EXPECT_EQ(event2.getMessage(), expectedMessage2);
    const auto& options2 = get<1>(logs->at(1));
    EXPECT_EQ(options2.logWithThread(), true);
    EXPECT_EQ(options2.logAsJson(), false);
    EXPECT_EQ(options2.logWithSource(), true);
}
