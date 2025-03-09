//
// Created by kolbe on 07.03.2025.
//

#ifndef CONSOLE_SINK_H
#define CONSOLE_SINK_H

#include <cpplog/sink.h>
#include <mutex>

using namespace std;
using namespace cpplog::common;

namespace cpplog::sinks {
  class ConsoleSink final : public Sink {
  public:
  	void log(const Log& log) const override;
  private:
  	static std::mutex mtx;
  };
}

#endif //CONSOLE_SINK_H
