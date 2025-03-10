//
// Created by psp515 on 10.03.2025.
//

#include <iostream>
#include <string>
#include <format>
#include <chrono>
#include <cpplog/sinks/base_sink.h>
#include "../extensions/level_extensions.h"

using namespace std;
using namespace cpplog::sinks;
using namespace cpplog::extensions;

string BaseSink::format_message(const Log& log) const {
	const auto level_name = LevelExtensions::level_name(log.get_level());

	const auto current_time = log.get_timestamp();
	ostringstream oss;
	oss << put_time(localtime(&current_time), "%Y-%m-%d %H:%M:%S");
	const auto time_str = oss.str();

	const auto message = log.get_message();

	return format("[{}][{}] {}", level_name, time_str, message);
}