//
// Created by psp515 on 04.03.2025.
//

#ifndef SINK_H
#define SINK_H

#include <cpplog/common/log.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog {
    class Sink {
      public:
      virtual ~Sink() = default;
      virtual void log(const Log& log) const = 0;
    };
}

#endif //SINK_H
