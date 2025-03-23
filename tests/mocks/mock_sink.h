#ifndef MOCKSINK_H
#define MOCKSINK_H

#include <cpplog/sink.h>
#include <vector>
#include <cpplog/common/log.h>

namespace cpplog {
class MockSink : public Sink {
public:
	MockSink() = default;

	void log(const Log& log) const override {
		logs.push_back(log);
	}

	const std::vector<Log>& get_logs() const {
		return logs;
	}

	// Clear logs for test isolation
	void clear_logs() {
		logs.clear();
	}

private:
	mutable std::vector<Log> logs;
};
}

#endif // MOCKSINK_H
