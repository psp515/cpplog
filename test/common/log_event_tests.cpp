//
// Created by kolbe on 10.04.2025.
//

#include <chrono>
#include <cpplog/common/log_event.h>
#include <cpplog/common/log_level.h>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

using namespace cpplog::common;

TEST(LogEventTests, ConstructorWithoutSource_AssignsCorrectValues)
{
  // Arrange
  LogLevel level = INFO;
  std::string message = "Test message";

  // Act
  LogEvent event(level, message);

  // Assert
  EXPECT_EQ(event.getMessage(), message);
  EXPECT_EQ(event.getLevel(), level);
  EXPECT_EQ(event.getThread(), std::this_thread::get_id());
}

TEST(LogEventTests, ConstructorWithSource_AssignsSourceInfo)
{
  // Arrange
  LogLevel level = WARN;
  std::string message = "Source event";
  auto source = std::source_location::current();

  // Act
  LogEvent event(level, message, source);

  // Assert
  EXPECT_EQ(event.getMessage(), message);
  EXPECT_EQ(event.getLevel(), level);
  EXPECT_EQ(event.getThread(), std::this_thread::get_id());

  EXPECT_EQ(event.getSourceFileName(), source.file_name());
  EXPECT_EQ(event.getSourceFunctionName(), source.function_name());
}
