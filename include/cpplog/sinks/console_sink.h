//
// Created by psp515 on 07.03.2025.
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
	ConsoleSink() = default;
	~ConsoleSink() override = default;
	ConsoleSink(const ConsoleSink&) = delete;
	void log(const Log& log) const override;

private:
	static std::mutex mtx;
};
} // namespace cpplog::sinks

#endif //CONSOLE_SINK_H
