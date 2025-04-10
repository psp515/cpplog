//
// Created by kolbe on 08.04.2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <cpplog/common/log_level.h>
#include <cpplog/common/log_event.h>

using namespace cpplog::common;

namespace cpplog {

/**
* @brief Represents configurable logger class, used to catch
*/
class Logger {
public:

	explicit Logger(const LogLevel& level);

	Logger(Logger const&) = delete;
	Logger& operator=(Logger const&) = delete;
	~Logger() = default;



private:


};
}

#endif //LOGGER_H
