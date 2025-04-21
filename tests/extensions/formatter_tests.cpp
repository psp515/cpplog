//
// Created by psp515 on 18.04.2025.
//

#include <gtest/gtest.h>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_event_options.h>
#include <cpplog/common/log_level.h>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cpplog/extensions/formatter.h>

using namespace std;
using namespace cpplog;
using namespace cpplog::common;
using namespace cpplog::extensions;

TEST(FormatterTest, FormatWithoutThreadAndSource) {
    // Arrange
    LogEventOptions options(false, false, false);
    LogEvent event(INFO, "Message");
    auto formatter = Formatter(options);

    // Act
    auto result = formatter.format(event);

    // Assert
    EXPECT_TRUE(result.find("[INFO]") != string::npos);
    EXPECT_TRUE(result.find("[") != string::npos);
    EXPECT_EQ(count(result.begin(), result.end(), '['), 2);
    EXPECT_TRUE(result.find("Message") != string::npos);
}


TEST(FormatterTest, FormatWithDate) {
    // Arrange
    LogEventOptions options(false, false, false);
    LogEvent event(INFO, "Message");
    auto timestamp = event.getTime();
    auto formatter = Formatter(options);

    // Act
    auto result = formatter.format(event);

    // Assert
    EXPECT_TRUE(result.find(timestamp) != string::npos);
}

TEST(FormatterTest, FormatWithLevel) {
    // Arrange
    LogEventOptions options(false, false, false);
    LogEvent event(INFO, "Message");
    auto formatter = Formatter(options);

    // Act
    auto result = formatter.format(event);

    // Assert
    EXPECT_TRUE(result.find("[INFO]") != string::npos);
}

TEST(FormatterTest, FormatWithMessage) {
    // Arrange
    LogEventOptions options(false, false, false);
    LogEvent event(INFO, "Test Message");
    auto formatter = Formatter(options);

    // Act
    auto result = formatter.format(event);

    // Assert
    EXPECT_TRUE(result.find("Test Message") != string::npos);
}

TEST(FormatterTest, FormatWithThreadId) {
    // Arrange
    LogEventOptions options(false, true, false);
    LogEvent event(INFO, "Message");

    ostringstream threadIdStream;
    threadIdStream << event.getThread();
    auto threadIdStr = threadIdStream.str();
    auto formatter = Formatter(options);

    // Act
    auto result = formatter.format(event);

    // Assert
    EXPECT_TRUE(result.find("[") != string::npos);
    EXPECT_EQ(count(result.begin(), result.end(), '['), 3);
    EXPECT_TRUE(result.find("[" + threadIdStr + "]") != string::npos);
}

TEST(FormatterTest, FormatWithSourceFileAndFunction) {
    // Arrange
    LogEventOptions options(false, false, true);
    source_location source = source_location::current();
    LogEvent event(INFO, "Message", source);
    auto formatter = Formatter(options);

    // Act
    auto result = formatter.format(event);

    // Assert
    EXPECT_TRUE(result.find("[") != string::npos);
    EXPECT_EQ(count(result.begin(), result.end(), '['), 4);
    EXPECT_TRUE(result.find("FormatWithSourceFileAndFunction") != string::npos);
    EXPECT_TRUE(result.find("formatter_tests.cpp") != string::npos);
}

TEST(FormatterTest, FormatWithUnknownSourceFileAndFunction) {
    // Arrange
    LogEventOptions options(false, false, true);
    LogEvent event(INFO, "Message");
    auto formatter = Formatter(options);

    // Act
    auto result = formatter.format(event);

    // Assert
    EXPECT_TRUE(result.find("[") != string::npos);
    EXPECT_EQ(count(result.begin(), result.end(), '['), 4);
    EXPECT_TRUE(result.find("[Unknown]") != string::npos);
}

TEST(FormatterTest, FullFormatWithJson) {
    // Arrange
    LogEventOptions options(true, true, true);
    source_location source = source_location::current();
    LogEvent event(INFO, "Message", source);
    auto formatter = Formatter(options);

    // Act
    auto result = formatter.format(event);

    // Assert
    EXPECT_TRUE(result.find("{") != string::npos);
    EXPECT_TRUE(result.find("}") != string::npos);
    EXPECT_TRUE(result.find("\"message\":") != string::npos);
    EXPECT_TRUE(result.find("\"source_file\":") != string::npos);
    EXPECT_TRUE(result.find("\"source_function\":") != string::npos);
    EXPECT_TRUE(result.find("\"thread\":") != string::npos);
    EXPECT_TRUE(result.find("\"time\":") != string::npos);
    EXPECT_TRUE(result.find("\"level\":") != string::npos);
}

TEST(FormatterTest, DefaultFormatWithJson) {
    // Arrange
    LogEventOptions options(true, false, false);
    source_location source = source_location::current();
    LogEvent event(INFO, "Message", source);
    auto formatter = Formatter(options);

    // Act
    auto result = formatter.format(event);

    // Assert
    EXPECT_TRUE(result.find("{") != string::npos);
    EXPECT_TRUE(result.find("}") != string::npos);
    EXPECT_TRUE(result.find("\"message\":") != string::npos);
    EXPECT_TRUE(result.find("\"source_file\":") == string::npos);
    EXPECT_TRUE(result.find("\"source_function\":") == string::npos);
    EXPECT_TRUE(result.find("\"thread\":") == string::npos);
    EXPECT_TRUE(result.find("\"time\":") != string::npos);
    EXPECT_TRUE(result.find("\"level\":") != string::npos);
}