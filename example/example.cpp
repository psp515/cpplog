//
// Created by psp515 on 02.03.2025.
//

#define NOMINMAX
#define byte win_byte_override
#include <winsock2.h>
#include <windows.h>
#undef byte
#include <cstddef>


#include <exception>
#include <iostream>
#include <thread>
#include <random>
#include <chrono>
#include <ostream>
#include <cpplog/cpplog.h>
#include <cpplog/logger_configuration.h>
#include <cpplog/sinks/file_sink.h>

#include "http/win_http_sink.h"

using namespace cpplog;

void randomSleep(int minMs, int maxMs) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minMs, maxMs);

    const int timeout = dist(gen);
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
}

void threadActions()
{
    for (int i = 0; i < 5; ++i)
    {
        CppLog::error(source_location::current(),"Info Level log: {0}", i);
        randomSleep(100, 1500);
    }
}

void heartBeat()
{
    const auto options = LogEventOptions(false, true, false);

    auto local_logger = LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addStdoutSink()
        .build();

    local_logger->setLogEventOptions(options);

    while (true) {
        try
        {
            CppLog::info("Heartbeat log...");
            randomSleep(1000, 3000);
        } catch (std::exception &ex)
        {
            local_logger->error("Failed to send message. " + std::string(ex.what()));
        }
    }
}

int main() {
    try {
        std::cout << "Hello World!" << std::endl;

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
        CppLog::critical("Override file options");

        // Override options example 2
        // - Now message is json
        const auto jsonOptions = LogEventOptions(true, true, true);
        CppLog::setLogEventOptions(jsonOptions);
        CppLog::critical("json");

        // Override options
        CppLog::setLogEventOptions(options);

        CppLog::critical("Starting multi threading");

        // Threading example
        thread t1(threadActions);
        thread t2(threadActions);
        thread t3(threadActions);
        thread t4(threadActions);

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        // Example shows how to configure custom sink / this sink sends http messages to prepared server.
        CppLog::critical("Starting Http Example");

        const auto winOptions = WinHttpSinkOptions("/logs/single", "5254", "localhost");
        auto winSink = make_unique<WinHttpSink>(INFO, winOptions);

        LoggerConfiguration()
            .setLoggerFilteringLevel(INFO)
            .addSink(move(winSink))
            .configure();

        CppLog::setLogEventOptions(jsonOptions);

        thread th1(heartBeat);
        thread th2(heartBeat);

        th1.join();
        th2.join();

    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
}
