//
// Created by psp515 on 07.03.2025.
//

#include <algorithm>
#include <cpplog/common/level.h>
#include <cpplog/cpplog.h>
#include <cpplog/logger.h>
#include <cpplog/logger_configurator.h>
#include <cpplog/sinks/console_sink.h>
#include <cpplog/sinks/file_sink.h>

using namespace cpplog;
using namespace cpplog::sinks;

LoggerConfigurator& LoggerConfigurator::set_ignore_level(const level level) {
	ignore_level = level;
	return *this;
}

LoggerConfigurator& LoggerConfigurator::add_sink(unique_ptr<Sink> sink) {
	sinks.push_back(move(sink));
	return *this;
}

LoggerConfigurator& LoggerConfigurator::add_console_sink() {

	for(auto& sink : sinks) {
		if(dynamic_cast<ConsoleSink*>(sink.get()))
			return *this;
	}

	sinks.push_back(move(make_unique<ConsoleSink>()));
	return *this;
}

LoggerConfigurator& LoggerConfigurator::add_file_sink(const string& path) {
	for(auto& sink : sinks) {
		if(dynamic_cast<FileSink*>(sink.get()))
			return *this;
	}

	sinks.push_back(move(make_unique<FileSink>(path)));
	return *this;
}

LoggerConfigurator& LoggerConfigurator::add_file_sink(const string& path, ios_base::openmode mode) {
	sinks.push_back(move(make_unique<FileSink>(path, mode)));
	return *this;
}

unique_ptr<Logger> LoggerConfigurator::build() {
	if(!sinks.empty()) {
		return make_unique<Logger>(ignore_level, move(sinks));
	}

	return make_unique<Logger>(ignore_level);
}

void LoggerConfigurator::configure() {
	if(!sinks.empty()) {
		CppLog::configure(make_unique<Logger>(ignore_level, move(sinks)));
	} else {
		CppLog::configure(make_unique<Logger>(ignore_level));
	}
}
