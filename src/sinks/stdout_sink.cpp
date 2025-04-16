//
// Created by psp515 on 15.04.2025.
//

#include <cpplog/sinks/stdout_sink.h>
#include <iostream>
#include <mutex>

#include "../extensions/formatter.h"

using namespace std;
using namespace cpplog::sinks;
using namespace cpplog::extensions;

mutex StdoutSink::mtx;

void StdoutSink::log(const LogEventOptions &options, const LogEvent& event) {
    Formatter formatter;
    const auto log_message = formatter.format(options, event);

    lock_guard lock{mtx};
    cout << log_message << endl;
}
