//
// Created by psp515 on 02.03.2025.
//

#include <exception>
#include <iostream>
#include <thread>
#include <random>
#include <chrono>
#include <ostream>
#include <cpplog/cpplog.h>
#include <cpplog/logger_configuration.h>
#include <cpplog/sinks/file_sink.h>

using namespace std;
using namespace cpplog;

void randomSleep(int minMs, int maxMs) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minMs, maxMs);

    const int timeout = dist(gen);
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
}

void thread_actions()
{
    for (int i = 0; i < 5; ++i)
    {
        CppLog::error(source_location::current(),"Info Level log: {0}", i);
        randomSleep(100, 1500);
    }
}

int main() {
    try {
        cout << "Hello World!" << endl;

        // Configuration Example
        const auto opts = FileSinkOptions("logfile", "loggs", true);

        LoggerConfiguration().setLoggerFilteringLevel(INFO)
            .addStdoutSink()
            .addFileSink(opts, WARN)
            .configure();

        // Logging Example
        // - file sink skips messages for level lower than warning
        // - stdout displays everything since info level
        CppLog::debug("Debug Level");
        CppLog::info("Info Level");
        CppLog::warning("Warning Level");
        CppLog::error("Error Level");

        // Override options example 1
        // - Now message contains thread and source information
        const auto options = LogEventOptions(false, true, true);
        CppLog::setLogEventOptions(options);
        CppLog::critical("Override file options example");

        // Override options example 2
        // - Now message is json
        const auto jsonOptions = LogEventOptions(true, true, true);
        CppLog::setLogEventOptions(jsonOptions);
        CppLog::critical("Critical json");

        // Override options
        CppLog::setLogEventOptions(options);

        CppLog::critical("Starting multi threading");

        // Threading example
        thread t1(thread_actions);
        thread t2(thread_actions);
        thread t3(thread_actions);
        thread t4(thread_actions);

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        CppLog::critical("Final message thread");

        return 0;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
}
