//
// Created by kolbe on 08.03.2025.
//

#include <stdexcept>
#include <string>
#include <cpplog/common/level.h>
#include "LevelExtensions.h"

using namespace std;
using namespace cpplog::common;
using namespace cpplog::extensions;

string LevelExtensions::level_name(const level level) {
  switch (level) {
  case DEBUG:
    return "DEBUG";
  case INFO:
    return "INFO";
  case WARNING:
    return "WARNING";
  case ERROR:
    return "ERROR";
  case CRITICAL:
    return "CRITICAL";
  default:
    throw invalid_argument("Unknown log level");
  }
}