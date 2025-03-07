//
// Created by kolbe on 07.03.2025.
//

#ifndef CONSOLE_SINK_H
#define CONSOLE_SINK_H

#include <iostream>
#include <cpplog/sink.h>

using namespace std;

namespace cpplog::sinks {
  class ConsoleSink : public Sink {
  public:
    void log(const Log& log) const override {
       cout << log.get_message() << endl;
    }
  };
}

#endif //CONSOLE_SINK_H
