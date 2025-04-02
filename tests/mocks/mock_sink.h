#ifndef MOCKSINK_H
#define MOCKSINK_H

#include <cpplog/common/log.h>
#include <cpplog/sink.h>
#include <vector>

namespace cpplog::mocks {
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
} // namespace cpplog

#endif // MOCKSINK_H
