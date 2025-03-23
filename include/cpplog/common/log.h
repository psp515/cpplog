//
// Created by psp515 on 07.03.2025.
//

#ifndef LOG_H
#define LOG_H

#include <chrono>
#include <cpplog/common/level.h>
#include <source_location>
#include <sstream>

using namespace std;

namespace cpplog::common {
class Log {
public:
	Log(const level level, const string& message, const std::source_location& location) {

		this->level = level;
		this->message = message;
		this->timestamp = chrono::system_clock::to_time_t(chrono::system_clock::now());

		ostringstream oss;

		oss << location.file_name() << '(' << location.line() << ':' << location.column() << ")";

		this->file_data = oss.str();
		this->function_data = location.function_name();
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
	level level;
	time_t timestamp;
	string message;
	string file_data;
	string function_data;
};
} // namespace cpplog::common

#endif //LOG_H
