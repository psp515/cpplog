//
// Created by psp515 on 07.03.2025.
//

#ifndef STDOUT_SINK_H
#define STDOUT_SINK_H

#include <cpplog/sink.h>
#include <mutex>

using namespace std;
using namespace cpplog::common;

namespace cpplog::sinks {
class StdoutSink final : public Sink {
public:
	StdoutSink() = default;
	~StdoutSink() override = default;
	StdoutSink(const StdoutSink&) = delete;
	void log(const Log& log) const override;

private:
	static std::mutex mtx;
};
}

#endif //STDOUT_SINK_H
