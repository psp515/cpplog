//
// Created by kolbe on 14.03.2025.
//

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <ostream>
#include <filesystem>
#include <gtest/gtest.h>
#include <cpplog/common/log.h>
#include <cpplog/common/level.h>
#include <cpplog/sinks/file_sink.h>

using namespace std;
using namespace cpplog::sinks;
using namespace cpplog::common;

int Add(int a, int b) {
  return a + b;
}

// Test case
TEST(FileSinkTest, CreatesDataInFile) {
	// Arrange
  auto filename = "testFileSink.txt";
  auto sink = make_unique<FileSink>(filename);

  const filesystem::path dir(LOG_FOLDER);
  const filesystem::path file(filename);
  const filesystem::path full_path = dir / file;

  const auto now = chrono::system_clock::now();
  auto current_time = chrono::system_clock::to_time_t(now);
  ostringstream oss;
  oss << put_time(localtime(&current_time), "%Y-%m-%d %H:%M:%S");
  const auto message = "Example message on " + oss.str();

  auto line_written = false;

  // Act
  sink->log(Log(DEBUG, message));

  ifstream written_file(full_path);
  string line;
  while (getline(written_file, line)) {
    if (line.find(message)) {
      line_written = true;
      break;
    }
  }

  // Assert
  ASSERT_TRUE(line_written);
}
