//
// Created by psp515 on 07.03.2025.
//

#include <cpplog/logger.h>

using namespace std;
using namespace cpplog;


void Logger::debug(const string& message) const {
  if (this->ignore_level > DEBUG)
    return;

  this->log(DEBUG, message);
}

void Logger::info(const string& message) const {
  if (ignore_level > INFO)
    return;

  this->log(INFO, message);
}

void Logger::warning(const string& message) const {
  if (ignore_level > WARNING)
    return;

  this->log(WARNING, message);
}

void Logger::error(const string& message) const {
  if (ignore_level > ERROR)
    return;

  this->log(ERROR, message);
}

void Logger::critical(const string& message) const {
  if (ignore_level > CRITICAL)
    return;

  this->log(CRITICAL, message);
}

void Logger::log(const level level, const string& message) const {
  const auto log_message = new Log(level, message);
  this->log(*log_message);
}

void Logger::log(const Log& log) const {
  for (const auto& sink : this->sinks) {
    sink->log(log);
  }
}
