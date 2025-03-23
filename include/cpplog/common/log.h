//
// Created by psp515 on 07.03.2025.
//

#ifndef LOG_H
#define LOG_H

#include <thread>
#include <chrono>
#include <cpplog/common/level.h>
#include <source_location>

using namespace std;

namespace cpplog::common {
class Log {
public:
	Log(level level, const string& message, const std::source_location& location);
	Log(level level, const string& message);

	[[nodiscard]] std::thread::id get_thread() const {
		return this->thread;
	}

	[[nodiscard]] string get_file_data() const {
		return file_data;
	}

	[[nodiscard]] string get_function_data() const {
		return function_data;
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

private:
	std::thread::id thread;
	level level;
	time_t timestamp;
	string message;
	string file_data;
	string function_data;
};
} // namespace cpplog::common

#endif //LOG_H
