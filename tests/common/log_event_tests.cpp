//
// Created by psp515 on 10.04.2025.
//

#include <chrono>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_level.h>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <string>
#include <gtest/gtest.h>

using namespace cpplog::common;

TEST(LogEventTests, ConstructorWithoutSource_AssignsCorrectValues)
{
  // Arrange
  LogLevel level = INFO;
  string message = "Test message";

  // Act
  LogEvent event(level, message);

  // Assert
  EXPECT_EQ(event.getMessage(), message);
  EXPECT_EQ(event.getLevel(), level);
  EXPECT_EQ(event.getThread(), this_thread::get_id());
}

TEST(LogEventTests, ConstructorWithSource_AssignsSourceInfo)
{
  // Arrange
  LogLevel level = WARN;
  string message = "Source event";
  auto source = source_location::current();

  // Act
  LogEvent event(level, message, source);

  // Assert
  EXPECT_EQ(event.getMessage(), message);
  EXPECT_EQ(event.getLevel(), level);
  EXPECT_EQ(event.getThread(), this_thread::get_id());

  EXPECT_NE(event.getSourceFileName().find("log_event_tests.cpp"), string::npos);
  EXPECT_NE(event.getSourceFunctionName().find("ConstructorWithSource_AssignsSourceInfo"), string::npos);
}
