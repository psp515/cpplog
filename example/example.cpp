//
// Created by psp515 on 02.03.2025.
//

#include <exception>
#include <iostream>
#include <ostream>
#include <cpplog/cpplog.h>
#include <cpplog/logger_configuration.h>

using namespace std;
using namespace cpplog;

int main() {
    try {
        cout << "Hello World!" << endl;

        LoggerConfiguration configuration;
        FileSinkOptions opts;

        configuration.setLoggerFilteringLevel(INFO)
            .addStdoutSink()
            .addFileSink(FileSinkOptions(), WARN)
            .configure();

        CppLog::debug("Debug Level");
        CppLog::info("Info Level");
        CppLog::warning("Warning Level");
        CppLog::error("Error Level");

        const auto options = LogEventOptions(false, true, true);
        CppLog::setLogEventOptions(options);
        CppLog::critical("Critical");

        const auto jsonOptions = LogEventOptions(true, true, true);
        CppLog::setLogEventOptions(jsonOptions);
        CppLog::critical("Critical json");

        return 0;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
}
