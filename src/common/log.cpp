//
// Created by psp515 on 23.03.2025.
//

#include <thread>
#include <chrono>
#include <source_location>
#include <sstream>
#include <cpplog/common/log.h>
#include <cpplog/common/level.h>

using namespace cpplog::common;

Log::Log(const enum level level, const string& message, const std::source_location& location) {

	this->thread = std::this_thread::get_id();
	this->level = level;
	this->message = message;
	this->timestamp = std::chrono::system_clock::to_time_t(chrono::system_clock::now());

	ostringstream oss;
	oss << location.file_name() << '(' << location.line() << ':' << location.column() << ")";

	this->file_data = oss.str();
	this->function_data = location.function_name();
}

Log::Log(const enum level level, const string& message) {

	this->thread = std::this_thread::get_id();
	this->level = level;
	this->message = message;
	this->timestamp = std::chrono::system_clock::to_time_t(chrono::system_clock::now());
	this->function_data = "Unknown";
	this->file_data = "Unknown";
}