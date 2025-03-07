//
// Created by kolbe on 07.03.2025.
//

#ifndef LOG_H
#define LOG_H

#include <cpplog/common/level.h>

using namespace std;

namespace cpplog::common {
  class Log {
    public:
      Log(const level level, const string& message) : level(level), message(message) {}

      string get_message() const { return message; }

    private:
      level level;
      string message;

  };
}


#endif //LOG_H
