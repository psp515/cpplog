//
// Created by psp515 on 02.03.2025.
//


#include <exception>
#include <iostream>
#include <ostream>
#include <thread>

#include <cpplog/logger.h>
#include <cpplog/logger_builder.h>
#include <cpplog/common/level.h>
#include <cpplog/sinks/console_sink.h>

using namespace std;
using namespace cpplog;
using namespace cpplog::sinks;

int main() {
    try {
        LoggerBuilder builder;

        builder
            .set_ignore_level(DEBUG)
            .add_console_sink()
            .add_console_sink()
            .add_file_sink("tests.txt");

        const auto logger = builder.build();

        logger->debug(source_location::current(), "Debug {} {}", 2, 3);
        logger->debug("Hello World!");
        logger->info("Hello World!");
        logger->warning("Hello World!");
        logger->error("Hello World!");
        logger->critical("Hello World!");

        std::cout << std::this_thread::get_id() << endl;

        return 0;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
}
