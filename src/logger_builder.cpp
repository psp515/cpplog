//
// Created by kolbe on 07.03.2025.
//

#include <cpplog/common/level.h>
#include <cpplog/logger.h>
#include <cpplog/logger_builder.h>
#include <valarray>

using namespace cpplog;

LoggerBuilder& LoggerBuilder::set_ignore_level(const level level) {
  ignore_level = level;
	return *this;
}

LoggerBuilder& LoggerBuilder::add_sink(unique_ptr<Sink> sink)
{
	sinks.push_back(move(sink));
  return *this;
}

unique_ptr<Logger> LoggerBuilder::build()
{
  if (!sinks.empty()) {
    return make_unique<Logger>(ignore_level, move(sinks));
  }

  return make_unique<Logger>(ignore_level);
}

