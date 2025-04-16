//
// Created by psp515 on 15.04.2025.
//

#include <gtest/gtest.h>
#include <cpplog/logger.h>
#include <cpplog/logger_configuration.h>
#include <cpplog/common/log_level.h>
#include <source_location>

#include "mocks/mock_sink.h"

using namespace std;
using namespace cpplog;
using namespace cpplog::mocks;
using namespace cpplog::common;

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        mockSink = make_unique<MockSink>();
        mockSinkPtr = mockSink.get();
        logger = LoggerConfiguration()
                     .set_level(DEBUG)
                     .add_sink(std::move(mockSink))
                     .build();
    }

    unique_ptr<Logger> logger;
    MockSink* mockSinkPtr;
};

TEST(LoggerTest, LogsMessageAtDebugLevel) {
    // Arrange
    const std::string expectedMessage = "Debug message";

    // Act
    logger->debug(expectedMessage);

    // Assert
    const auto* logs = mockSinkPtr->get_logs();
    ASSERT_EQ(logs->size(), 1);

    const auto& logVariant = logs->at(0);
    ASSERT_TRUE(holds_alternative<LogEvent>(logVariant));
    const auto& event = get<LogEvent>(logVariant);
    EXPECT_EQ(event.getLevel(), DEBUG);
    EXPECT_EQ(event.getMessage(), expectedMessage);
}

TEST(LoggerTest, DoesNotLogBelowConfiguredLevel) {
    // Arrange
    auto newSink = std::make_unique<MockSink>();
    auto* rawSink = newSink.get();
    auto newLogger = LoggerConfiguration()
                         .set_level(WARN)
                         .add_sink(std::move(newSink))
                         .build();

    // Act
    newLogger->info("This should not be logged");

    // Assert
    const auto* logs = rawSink->get_logs();
    EXPECT_TRUE(logs->empty());
}

TEST(LoggerTest, LogsWithExplicitSourceLocation) {
    // Arrange
    const std::string msg = "Log with explicit location";
    const auto loc = std::source_location::current();

    // Act
    logger->info(msg, loc);

    // Assert
    const auto* logs = mockSinkPtr->get_logs();
    ASSERT_EQ(logs->size(), 1);

    const auto& event = get<LogEvent>(logs->at(0));
    EXPECT_EQ(event.getMessage(), msg);
    EXPECT_EQ(event.getSourceLocation().line(), loc.line());
    EXPECT_STREQ(event.getSourceLocation().file_name(), loc.file_name());
}

TEST(LoggerTest, LogsWithImplicitSourceLocation) {
    // Arrange
    const std::string msg = "Auto-source-location message";

    // Act
    logger->error(msg);

    // Assert
    const auto* logs = mockSinkPtr->get_logs();
    ASSERT_EQ(logs->size(), 1);

    const auto& event = get<LogEvent>(logs->at(0));
    EXPECT_EQ(event.getLevel(), ERROR);
    EXPECT_EQ(event.getMessage(), msg);
    EXPECT_TRUE(std::string(event.getSourceLocation().file_name()).find("logger_test") != std::string::npos);
}

TEST(LoggerTest, LogsFormattedMessageCorrectly) {
    // Arrange
    const auto loc = std::source_location::current();
    const std::string expectedMessage = "Value: 42";

    // Act
    logger->warning(loc, "Value: {}", 42);

    // Assert
    const auto* logs = mockSinkPtr->get_logs();
    ASSERT_EQ(logs->size(), 1);

    const auto& event = get<LogEvent>(logs->at(0));
    EXPECT_EQ(event.getLevel(), WARN);
    EXPECT_EQ(event.getMessage(), expectedMessage);
}