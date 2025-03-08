//
// Created by kolbe on 08.03.2025.
//

#include "../extensions/LevelExtensions.h"
#include <chrono>
#include <cpplog/sinks/console_sink.h>
#include <format>
#include <iostream>
#include <mutex>

using namespace std;
using namespace cpplog::sinks;
using namespace cpplog::extensions;

std::mutex ConsoleSink::mtx;

void ConsoleSink::log(const Log& log) const {
  const auto level_name = LevelExtensions::level_name(log.get_level());
  const auto now = chrono::system_clock::now();
  const auto current_time = chrono::system_clock::to_time_t(now);
  const auto time = put_time(localtime(&current_time), "%Y-%m-%d %H:%M:%S");
  const auto message = log.get_message();

  lock_guard lock{mtx};

  cout << "[" << level_name << "] ";
  cout << "[" << time << "] ";
  cout << message << endl;

}