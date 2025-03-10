//
// Created by kolbe on 08.03.2025.
//

#include "../extensions/level_extensions.h"
#include <cpplog/sinks/base_sink.h>
#include <cpplog/sinks/console_sink.h>
#include <iostream>
#include <mutex>

using namespace std;
using namespace cpplog::sinks;
using namespace cpplog::extensions;

mutex ConsoleSink::mtx;

void ConsoleSink::log(const Log& log) const {
  const auto log_message = format_message(log);
  lock_guard lock{mtx};
  cout << log_message << endl;
}