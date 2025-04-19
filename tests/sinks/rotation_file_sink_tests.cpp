//
// Created by psp515 on 19.04.2025.
//

#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <gtest/gtest.h>
#include <cpplog/logger.h>
#include <cpplog/cpplog.h>
#include <cpplog/common/rotation_file_sink_options.h>
#include <cpplog/sinks/rotation_file_sink.h>
#include <cpplog/logger_configuration.h>

#include "../helpers/file_helpers.h"

using namespace std;
using namespace cpplog;
using namespace cpplog::helpers;

TEST(RotationFileSinkTests, LogsMessages)
{
    // Arrange
    const string expectedMessage = "Debug message";
    const auto options = RotationFileSinkOptions(
        1,
        1024,
        "logs_messages.txt",
        "logs",
        true);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options)
        .configure();

    // Act
    CppLog::info(expectedMessage);
    const auto output = rotationReadFileToEnd(options);

    // Assert
    EXPECT_TRUE(output.find("[") != string::npos);
    EXPECT_EQ(count(output.begin(), output.end(), '['), 2);
    EXPECT_TRUE(output.find("FilteringWorks") == string::npos);
    EXPECT_TRUE(output.find("stdout_sink_tests.cpp") == string::npos);
}

TEST(RotationFileSinkTests, SinkFilteringWorks)
{
    // Arrange
    const string expectedMessage = "Filtering message";
    const auto options = RotationFileSinkOptions(
        1,
        1024,
        "sink_filtering_works.txt",
        "logs",
        true);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options, WARN)
        .configure();

    // Act
    CppLog::info(expectedMessage);
    const auto output = rotationReadFileToEnd(options);

    // Assert
    EXPECT_TRUE(output.find("[") == string::npos);
    EXPECT_TRUE(output.find("SinkFilteringWorks") == string::npos);
    EXPECT_TRUE(output.find("stdout_sink_tests.cpp") == string::npos);
}

TEST(RotationFileSinkTests, OverrideOptionsWorks)
{
    // Arrange
    const string expectedMessage = "Debug message";
    const auto options = RotationFileSinkOptions(
        1,
        1024,
        "override_options_works.txt",
        "logs",
        true);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options)
        .configure();

    // Act
    CppLog::setLogEventOptions(LogEventOptions(false, false, true));
    CppLog::info(expectedMessage);
    const auto output = rotationReadFileToEnd(options);

    // Assert
    EXPECT_TRUE(output.find("[") != string::npos);
    EXPECT_EQ(count(output.begin(), output.end(), '['), 4);
    EXPECT_TRUE(output.find("OverrideOptionsWorks") != string::npos);
    EXPECT_TRUE(output.find("file_sink_tests.cpp") != string::npos);
}

TEST(RotationFileSinkTests, LogAsJson)
{
    // Arrange
    const string expectedMessage = "Debug message";
    const auto options = RotationFileSinkOptions(
        1,
        1024,
        "json_works.txt",
        "logs",
        true);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options)
        .configure();

    // Act
    CppLog::setLogEventOptions(LogEventOptions(true, false, true));
    CppLog::info(expectedMessage);
    const auto output = rotationReadFileToEnd(options);

    // Assert
    EXPECT_TRUE(output.find("LogAsJson") != string::npos);
    EXPECT_TRUE(output.find("file_sink_tests.cpp") != string::npos);
    EXPECT_TRUE(output.find("\"message\":") != string::npos);
    EXPECT_TRUE(output.find("\"source_file\":") != string::npos);
    EXPECT_TRUE(output.find("\"source_function\":") != string::npos);
    EXPECT_TRUE(output.find("\"time\":") != string::npos);
    EXPECT_TRUE(output.find("\"level\":") != string::npos);
}

TEST(RotationFileSinkTests, CleansFileOnInitialize)
{
    // Arrange
    const string notExpectedMessage = "Debug message - cleared";
    const string expectedMessage = "Debug message 2";
    const auto options = RotationFileSinkOptions(
        1,
        1024,
        "cleans_on_initialize.txt",
        "logs",
        true);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options)
        .configure();

    // Act
    CppLog::info(notExpectedMessage);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options)
        .configure();

    CppLog::info(expectedMessage);

    const auto output = rotationReadFileToEnd(options);

    // Assert
    EXPECT_TRUE(output.find(expectedMessage) != string::npos);
    EXPECT_TRUE(output.find(notExpectedMessage) == string::npos);
}

TEST(RotationFileSinkTests, DoesNotCleanOnInitialize)
{
    // Arrange
    const string expectedMessage = "Debug message";
    const auto options1 = RotationFileSinkOptions(
        0,
        1024,
        "dont_clean.txt",
        "logs",
        true);
    const auto options2 = RotationFileSinkOptions(
        3,
        1024,
        "dont_clean.txt",
        "logs",
        false);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options1)
        .configure();

    // Act
    CppLog::info(expectedMessage);
    
    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options2)
        .configure();

    CppLog::info(expectedMessage);

    const auto output = rotationReadFileToEnd(options2);
    const auto files = countFilesWithBaseName(options2);

    size_t count = 0;
    size_t pos = 0;
    while ((pos = output.find(expectedMessage, pos)) != string::npos) {
        ++count;
        pos += expectedMessage.length();
    }

    // Assert
    EXPECT_TRUE(output.find(expectedMessage) != string::npos);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(files, 2);
}


TEST(RotationFileSinkTests, ExceptionOnTooLargeMessage)
{
    // Arrange
    const string expectedMessage = string(1025, 'A');
    const auto options = RotationFileSinkOptions(
        1,
        1,
        "too_large_message.txt",
        "logs",
        true);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options)
        .configure();

    // Act & Assert
    EXPECT_THROW({
        CppLog::info(expectedMessage);
    }, runtime_error);
}

TEST(RotationFileSinkTests, RotatesFile)
{
    // Arrange
    const string expectedMessage = string(600, 'A');
    const auto options = RotationFileSinkOptions(
        2,
        1,
        "rotates_files.txt",
        "logs",
        true);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options)
        .configure();

    // Act
    CppLog::info(expectedMessage);
    CppLog::info(expectedMessage);
    CppLog::info(expectedMessage);

    const auto files = countFilesWithBaseName(options);

    // Assert
    EXPECT_EQ(files, 3);
}

TEST(RotationFileSinkTests, RemovesFiles)
{
    // Arrange
    const string expectedMessage = string(600, 'A');
    const auto options = RotationFileSinkOptions(
        2,
        1,
        "remove_files.txt",
        "logs",
        true);

    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addRotationFileSink(options)
        .configure();

    // Act
    CppLog::info(expectedMessage);
    CppLog::info(expectedMessage);
    CppLog::info(expectedMessage);
    CppLog::info(expectedMessage);
    CppLog::info(expectedMessage);

    const auto files = countFilesWithBaseName(options);

    // Assert
    EXPECT_EQ(files, 3);
}