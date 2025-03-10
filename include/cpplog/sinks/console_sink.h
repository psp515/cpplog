//
// Created by kolbe on 07.03.2025.
//

#ifndef CONSOLE_SINK_H
#define CONSOLE_SINK_H

#include <mutex>
#include <cpplog/sink.h>
#include <cpplog/sinks/base_sink.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog::sinks {
  class ConsoleSink final : public BaseSink {
  public:
  	ConsoleSink() = default;
  	~ConsoleSink() override = default;
  	ConsoleSink(const ConsoleSink&) = delete;
  	void log(const Log& log) const override;
  private:
  	static std::mutex mtx;
  };
}

#endif //CONSOLE_SINK_H
