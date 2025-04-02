//
// Created by psp515 on 23.03.2025.
//

#include "../extensions/level_extensions.h"

#include <chrono>
#include <cpplog/common/level.h>
#include <cpplog/common/log.h>
#include <source_location>
#include <sstream>
#include <thread>

using namespace cpplog::common;
using namespace cpplog::extensions;

Log::Log(const enum level level,
		 const string& message,
		 const source_location& location,
		 const bool& attach_source,
		 const bool& attach_thread) {

	this->thread = this_thread::get_id();
	this->level = level;
	this->message = message;
	this->timestamp = chrono::system_clock::to_time_t(chrono::system_clock::now());

	ostringstream oss;
	oss << location.file_name() << '(' << location.line() << ':' << location.column() << ")";

	this->source_location_file = oss.str();
	this->source_location_function = location.function_name();

	this->attach_source = attach_source;
	this->attach_thread = attach_thread;
}

Log::Log(const enum level level,
		 const string& message,
		 const bool& attach_source,
		 const bool& attach_thread) {

	this->thread = this_thread::get_id();
	this->level = level;
	this->message = message;
	this->timestamp = chrono::system_clock::to_time_t(chrono::system_clock::now());

	this->source_location_function = "Unknown";
	this->source_location_file = "Unknown";

	this->attach_source = attach_source;
	this->attach_thread = attach_thread;
}

string Log::get_formatted_message() const {
	const auto level_name = LevelExtensions::level_name(this->level);

	ostringstream time_string;
	time_string << put_time(localtime(&this->timestamp), "%Y-%m-%d %H:%M:%S");
	const auto time = time_string.str();

	ostringstream formatted;

	formatted << "[" << level_name << "] ";
	formatted << "[" << level_name << "] ";

	if(attach_thread) {
		formatted << "[" << level_name << "] ";
	}

	if(attach_source) {
		formatted << "[" << source_location_file << "] ";
		formatted << "[" << source_location_function << "] ";
	}

	formatted << "[" << message << "] ";

	return formatted.str();
}
