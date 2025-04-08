//
// Created by psp515 on 04.03.2025.
//

#ifndef LOGGERCONFIGURATOR_H
#define LOGGERCONFIGURATOR_H

#include <cpplog/common/level.h>
#include <cpplog/logger.h>
#include <cpplog/sink.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog {
class LoggerConfigurator final {
public:
	~LoggerConfigurator() = default;
	LoggerConfigurator& add_sink(unique_ptr<Sink> sink);
	LoggerConfigurator& add_console_sink();
	LoggerConfigurator& add_file_sink(const string& path);
	LoggerConfigurator& add_file_sink(const string& path, ios_base::openmode mode);
	LoggerConfigurator& set_ignore_level(level level);
	unique_ptr<Logger> build();
	void configure();

private:
	vector<unique_ptr<Sink>> sinks;
	level ignore_level = DEBUG;
};
} // namespace cpplog

#endif //LOGGERCONFIGURATOR_H
