#ifndef CPPLOG_H
#define CPPLOG_H

#include <cpplog/logger.h>
#include <memory>
#include <source_location>
#include <string>

namespace cpplog {

class CppLog {
public:
	static void configure(std::unique_ptr<Logger> logger) {
		instance = std::move(logger);
	}

	template <class... Args>
	static void
	debug(const std::source_location& location, const std::string& fmt, Args&&... args) {
		if(instance) {
			instance->debug(location, fmt, std::forward<Args>(args)...);
		}
	}

	static void debug(const std::string& message,
					  const std::source_location& location = std::source_location::current()) {
		if(instance) {
			instance->debug(message, location);
		}
	}

	static void info(const std::string& message,
					 const std::source_location& location = std::source_location::current()) {
		if(instance) {
			instance->info(message, location);
		}
	}

	template <class... Args>
	static void info(const std::source_location& location, const std::string& fmt, Args&&... args) {
		if(instance) {
			instance->info(location, fmt, std::forward<Args>(args)...);
		}
	}

	static void warning(const std::string& message,
						const std::source_location& location = std::source_location::current()) {
		if(instance) {
			instance->warning(message, location);
		}
	}

	template <class... Args>
	static void
	warning(const std::source_location& location, const std::string& fmt, Args&&... args) {
		if(instance) {
			instance->warning(location, fmt, std::forward<Args>(args)...);
		}
	}

	static void error(const std::string& message,
					  const std::source_location& location = std::source_location::current()) {
		if(instance) {
			instance->error(message, location);
		}
	}

	template <class... Args>
	static void
	error(const std::source_location& location, const std::string& fmt, Args&&... args) {
		if(instance) {
			instance->error(location, fmt, std::forward<Args>(args)...);
		}
	}

	static void critical(const std::string& message,
						 const std::source_location& location = std::source_location::current()) {
		if(instance) {
			instance->critical(message, location);
		}
	}

	template <class... Args>
	static void
	critical(const std::source_location& location, const std::string& fmt, Args&&... args) {
		if(instance) {
			instance->critical(location, fmt, std::forward<Args>(args)...);
		}
	}

private:
	static std::unique_ptr<Logger> instance;
};

} // namespace cpplog

#endif // CPPLOG_H
