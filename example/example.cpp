//
// Created by psp515 on 02.03.2025.
//

#include <cpplog/cpplog.h>
#include <exception>
#include <iostream>
#include <ostream>

#include <cpplog/common/level.h>
#include <cpplog/logger.h>
#include <cpplog/logger_configurator.h>
#include <cpplog/sinks/console_sink.h>

using namespace std;
using namespace cpplog;
using namespace cpplog::sinks;

int main() {
    try {
        LoggerConfigurator builder;

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

    	CppLog::info("No Hello World!");

        LoggerConfigurator builder2;
    	builder2
    		.set_ignore_level(INFO)
    		.add_console_sink()
    		.configure_default();

    	CppLog::debug("No Hello World!");
		CppLog::info("Hello World!");

        return 0;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
}
