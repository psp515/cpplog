//
// Created by psp515 on 18.04.2025.
//

#include <string>
#include <gtest/gtest.h>
#include <cpplog/logger.h>
#include <cpplog/cpplog.h>
#include <cpplog/logger_configuration.h>

using namespace std;
using namespace cpplog;

TEST(StdOutSinkTests, LogsMessages) {
    // Arrange
    const string expectedMessage = "Debug message";

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

TEST(StdOutSinkTests, SinkFilteringWorks) {
    // Arrange
    const string expectedMessage = "Debug message";

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addStdoutSink(WARN)
        .configure();

    // Act
    streambuf* orig_buf = cout.rdbuf();
    stringstream buffer;
    cout.rdbuf(buffer.rdbuf());
    CppLog::info(expectedMessage);
    cout.rdbuf(orig_buf);
    const auto output = buffer.str();

    // Assert
    EXPECT_TRUE(output.find("[") == string::npos);
    EXPECT_TRUE(output.find("SinkFilteringWorks") == string::npos);
    EXPECT_TRUE(output.find("stdout_sink_tests.cpp") == string::npos);
}

TEST(StdOutSinkTests, OverrideOptionsWorks) {
    // Arrange
    const string expectedMessage = "Debug message";

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addStdoutSink()
        .configure();

    // Act
    streambuf* orig_buf = cout.rdbuf();
    stringstream buffer;
    cout.rdbuf(buffer.rdbuf());
    CppLog::setLogEventOptions(LogEventOptions(false, false, true));
    CppLog::info(expectedMessage);
    cout.rdbuf(orig_buf);
    auto output = buffer.str();

    // Assert
    EXPECT_TRUE(output.find("[") != string::npos);
    EXPECT_EQ(count(output.begin(), output.end(), '['), 4);
    EXPECT_TRUE(output.find("OverrideOptionsWorks") != string::npos);
    EXPECT_TRUE(output.find("stdout_sink_tests.cpp") != string::npos);
}

TEST(StdOutSinkTests, LogAsJson) {
    // Arrange
    const string expectedMessage = "Debug message";

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addStdoutSink()
        .configure();

    // Act
    streambuf* orig_buf = cout.rdbuf();
    stringstream buffer;
    cout.rdbuf(buffer.rdbuf());
    CppLog::setLogEventOptions(LogEventOptions(true, false, true));
    CppLog::info(expectedMessage);
    cout.rdbuf(orig_buf);
    auto output = buffer.str();

    // Assert
    EXPECT_TRUE(output.find("LogAsJson") != string::npos);
    EXPECT_TRUE(output.find("stdout_sink_tests.cpp") != string::npos);
    EXPECT_TRUE(output.find("\"message\":") != string::npos);
    EXPECT_TRUE(output.find("\"source_file\":") != string::npos);
    EXPECT_TRUE(output.find("\"source_function\":") != string::npos);
    EXPECT_TRUE(output.find("\"time\":") != string::npos);
    EXPECT_TRUE(output.find("\"level\":") != string::npos);
}
