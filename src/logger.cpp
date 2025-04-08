//
// Created by psp515 on 07.03.2025.
//

#include <cpplog/logger.h>
#include <source_location>

using namespace std;
using namespace cpplog;

void Logger::log(const level level,
				 const string& message,
				 const std::source_location& location) const {

	const auto log_message = new Log(level, message, location, attach_source, attach_thread);
	this->log(*log_message);
}

void Logger::log(const Log& log) const {
	if(ignore_level > log.get_level())
		return;

	for(const auto& sink : this->sinks) {
		sink->log(log);
	}
}
