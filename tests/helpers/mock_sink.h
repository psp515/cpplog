#ifndef MOCKSINK_H
#define MOCKSINK_H

#include <cpplog/common/log_event_options.h>
#include <cpplog/common/log_event.h>
#include <cpplog/sink.h>
#include <vector>
#include <memory>

using namespace std;

namespace cpplog::helpers {

	class MockSink final : public Sink {
	public:

  		MockSink() = delete;

	    explicit MockSink(const LogLevel &level, const shared_ptr<vector<pair<LogEvent, LogEventOptions>>> &logs) : Sink(level), logs(logs) {
	    }

		void log(const LogEventOptions& options, const LogEvent& event) override {
    		logs->push_back({event, options});
		}

	private:
		shared_ptr<vector<pair<LogEvent, LogEventOptions>>> logs;
};

} // namespace cpplog

#endif // MOCKSINK_H
