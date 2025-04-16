#ifndef MOCKSINK_H
#define MOCKSINK_H

#include <cpplog/common/log_event_options.h>
#include <cpplog/common/log_event.h>
#include <cpplog/sink.h>
#include <vector>

using namespace std;

namespace cpplog::mocks {

class MockSink final : public Sink {
public:

	void log(const LogEventOptions& options, const LogEvent& event) override {
		logs.push_back(event);
	}

	const vector<variant<LogEvent, LogEventOptions>>* get_logs() const {
		return &logs;
	}

	// Clear logs for test isolation
	void clear_logs() const {
		logs.clear();
	}

private:
	mutable vector<variant<LogEvent, LogEventOptions>> logs;
};

} // namespace cpplog

#endif // MOCKSINK_H
