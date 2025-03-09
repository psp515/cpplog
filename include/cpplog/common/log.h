//
// Created by kolbe on 07.03.2025.
//

#ifndef LOG_H
#define LOG_H

#include <iomanip>
#include <chrono>
#include <utility>
#include <cpplog/common/level.h>

using namespace std;

namespace cpplog::common {
  class Log {
    public:
      Log(const level level, string message) : level(level), message(std::move(message)) {
        const auto now = chrono::system_clock::now();
        timestamp = chrono::system_clock::to_time_t(now);
      }

      [[nodiscard]] time_t get_timestamp() const { return timestamp; }
      [[nodiscard]] string get_message() const { return message; }
      [[nodiscard]] level get_level() const { return level; }

  private:
      level level;
      string message;
      time_t timestamp;
  };
}


#endif //LOG_H
