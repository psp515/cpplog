//
// Created by psp515 on 08.03.2025.
//

#include "../extensions/level_extensions.h"
#include <cpplog/sinks/console_sink.h>
#include <iostream>
#include <mutex>

using namespace std;
using namespace cpplog::sinks;
using namespace cpplog::extensions;

mutex ConsoleSink::mtx;

void ConsoleSink::log(const Log& log) const {
	const auto log_message = log.get_formatted_message();
	lock_guard lock{mtx};
	cout << log_message << endl;
}