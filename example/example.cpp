//
// Created by psp515 on 02.03.2025.
//


#include <exception>
#include <iostream>
#include <ostream>

#include <cpplog/logger.h>
#include <cpplog/common/level.h>
#include <cpplog/sinks/console_sink.h>

using namespace std;
using namespace cpplog;
using namespace cpplog::sinks;

int main() {
    try {
        cout << "Initializing example." << endl;

        const auto logger = new Logger(ERROR);

        logger->debug("Hello World!");
        logger->info("Hello World!");
        logger->critical("Hello World!");
        logger->warning("Hello World!");
        logger->error("Hello World!");
        logger->critical("Hello World!");

        return 0;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
}
