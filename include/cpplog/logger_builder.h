//
// Created by psp515 on 04.03.2025.
//

#ifndef ILOGGERBUILDER_H
#define ILOGGERBUILDER_H

#include <cpplog/sink.h>
#include <cpplog/logger.h>
#include <cpplog/common/level.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog {
    class LoggerBuilder {
          public:
          virtual ~LoggerBuilder(){}
          virtual void add_sink(Sink sink) = 0;
          virtual void set_target(level level) = 0;
          virtual Logger& build() = 0;
    };
}

#endif //ILOGGERBUILDER_H
