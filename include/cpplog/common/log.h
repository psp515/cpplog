//
// Created by kolbe on 07.03.2025.
//

#ifndef LOG_H
#define LOG_H

#include <utility>
#include <cpplog/common/level.h>

using namespace std;

namespace cpplog::common {
  class Log {
    public:
      Log(const level level, string message) : level(level), message(std::move(message)) {}

      [[nodiscard]] string get_message() const { return message; }
      [[nodiscard]] level get_level() const { return level; }

  private:
      level level;
      string message;
  };
}


#endif //LOG_H
