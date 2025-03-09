//
// Created by psp515 on 09.03.2025.
//

#include "../extensions/level_extensions.h"
#include <cpplog/sinks/file_sink.h>

using namespace std;
using namespace cpplog::sinks;
using namespace cpplog::extensions;

mutex FileSink::mtx;

void FileSink::log(const Log& log) const {
	const auto level_name = LevelExtensions::level_name(log.get_level());
	const auto current_time = log.get_timestamp();
	const auto time = put_time(localtime(&current_time), "%Y-%m-%d %H:%M:%S");
	const auto message = log.get_message();

	lock_guard lock{mtx};


}
