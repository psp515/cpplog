//
// Created by kolbe on 09.04.2025.
//

#ifndef LOG_ENVENT_H
#define LOG_ENVENT_H

#include <cpplog/common/log_level.h>
#include <source_location>
#include <thread>
#include <chrono>

using namespace std;

namespace cpplog::common {

/** Class represents single event in system with registered values.
*
*/
class LogEvent {
public:

	/**
	*
	*/
	LogEvent() = delete;

	/** Creates LogEvent with source.
	* /param level
	* */
	explicit LogEvent(LogLevel& level, string& message, const source_location& source) : LogEvent(level, message) {
		this->source = source;
		this->has_source = true;
	};


	explicit LogEvent(LogLevel& level, string& message) : message(message), level(level), has_source(false) {
		this->thread = this_thread::get_id();
		this->timestamp = chrono::system_clock::to_time_t(chrono::system_clock::now());
	};

	[[nodiscard]] string getMessage() {
		return message;
	};

	[[nodiscard]] LogLevel getLevel() {
		return level;
	};

	[[nodiscard]] thread::id getThread() {
		return thread;
	}

	[[nodiscard]] string getSourceFunctionName();
	[[nodiscard]] string getSourceFileName();
	[[nodiscard]] string getTime();

private:
	LogLevel level;
	thread::id thread;
	time_t timestamp;

	string message;

	bool has_source;
	source_location source;
};
}

#endif //LOG_ENVENT_H
