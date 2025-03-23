//
// Created by psp515 on 02.03.2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <cpplog/common/level.h>
#include <cpplog/common/log.h>
#include <cpplog/sink.h>
#include <cpplog/sinks/console_sink.h>
#include <format>
#include <memory>
#include <source_location>
#include <string>
#include <vector>

using namespace cpplog::common;
using namespace cpplog::sinks;

namespace cpplog {
class Logger final {
public:
	explicit Logger(const level ignore_level)
		: ignore_level(ignore_level) { };

	explicit Logger(const level ignore_level, vector<unique_ptr<Sink>> sinks)
		: ignore_level(ignore_level)
		, sinks(move(sinks)) { };

	Logger(const Logger&) = delete;
	Logger& operator<=>(const Logger&) = delete;
	~Logger() = default;

	template <class... Args>
	void debug(const std::source_location& location, format_string<Args...> fmt, Args&&... args) {
		if(this->ignore_level > DEBUG)
			return;

		this->log(DEBUG, location, fmt, forward<Args>(args)...);
	}

	void debug(const string& message,
			   const std::source_location& location = std::source_location::current()) const;

	template <class... Args>
	void info(const std::source_location& location, format_string<Args...> fmt, Args&&... args) {
		if(this->ignore_level > INFO)
			return;

		this->log(INFO, location, fmt, forward<Args>(args)...);
	}

	void info(const string& message,
			  const std::source_location& location = std::source_location::current()) const;

	template <class... Args>
	void warning(const std::source_location& location, format_string<Args...> fmt, Args&&... args) {
		if(this->ignore_level > WARNING)
			return;

		this->log(WARNING, location, fmt, forward<Args>(args)...);
	}

	void warning(const string& message,
				 const std::source_location& location = std::source_location::current()) const;

	template <class... Args>
	void error(const std::source_location& location, format_string<Args...> fmt, Args&&... args) {
		if(this->ignore_level > ERROR)
			return;

		this->log(ERROR, location, fmt, forward<Args>(args)...);
	}

	void error(const string& message,
			   const std::source_location& location = std::source_location::current()) const;

	template <class... Args>
	void
	critical(const std::source_location& location, format_string<Args...> fmt, Args&&... args) {
		if(this->ignore_level > CRITICAL)
			return;

		this->log(CRITICAL, location, fmt, forward<Args>(args)...);
	}

	void critical(const string& message,
				  const std::source_location& location = std::source_location::current()) const;

private:
	void log(const Log& log) const;
	void log(level level, const string& message, const std::source_location& location) const;

	template <class... Args>
	void log(const level level,
			 const std::source_location& location,
			 const format_string<Args...> fmt,
			 Args&&... args) const {
		this->log(level, format(fmt, forward<Args>(args)...), location);
	}

	level ignore_level;
	std::vector<std::unique_ptr<Sink>> sinks;
};
} // namespace cpplog

#endif //LOGGER_H
