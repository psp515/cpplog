//
// Created by psp515 on 04.03.2025.
//

#ifndef LOGGERBUILDER_H
#define LOGGERBUILDER_H

#include <cpplog/sink.h>
#include <cpplog/logger.h>
#include <cpplog/common/level.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog {
  class LoggerBuilder final {
  public:
    ~LoggerBuilder() = default;
    LoggerBuilder& add_sink(unique_ptr<Sink> sink);
    LoggerBuilder& add_console_sink();
	LoggerBuilder& add_file_sink(const string& path);
	LoggerBuilder& add_file_sink(const string& path, ios_base::openmode mode);
	LoggerBuilder& set_ignore_level(level level);
	  unique_ptr<Logger> build();
  private:
    vector<unique_ptr<Sink>> sinks;
	level ignore_level = DEBUG;
  };
}

#endif //LOGGERBUILDER_H
