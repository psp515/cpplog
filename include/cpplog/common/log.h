//
// Created by psp515 on 07.03.2025.
//

#ifndef LOG_H
#define LOG_H

#include <cpplog/common/level.h>
#include <source_location>
#include <thread>

using namespace std;

namespace cpplog::common {
class Log {
public:
	Log(level level,
		const string& message,
		const source_location& location,
		const bool& attach_source,
		const bool& attach_thread);
	Log(level level, const string& message, const bool& attach_source, const bool& attach_thread);

	[[nodiscard]] thread::id get_thread() const {
		return this->thread;
	}

	[[nodiscard]] string get_source_location_file() const {
		return source_location_file;
	}

	[[nodiscard]] string get_source_location_function() const {
		return source_location_function;
	}

	[[nodiscard]] string get_message() const {
		return message;
	}

	[[nodiscard]] time_t get_timestamp() const {
		return timestamp;
	}

	[[nodiscard]] level get_level() const {
		return level;
	}

	[[nodiscard]] bool should_attach_source() const {
		return attach_source;
	}

	[[nodiscard]] bool should_attach_thread() const {
		return attach_thread;
	}

	[[nodiscard]] string get_formatted_message() const;

private:
	thread::id thread;
	level level;
	time_t timestamp;

	bool attach_source;
	bool attach_thread;

	string message;
	string source_location_file;
	string source_location_function;
};
} // namespace cpplog::common

#endif //LOG_H
