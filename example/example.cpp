//
// Created by psp515 on 02.03.2025.
//


#include <exception>
#include <iostream>
#include <ostream>

#include "cpplog/ILogger.h"
#include "cpplog/BaseLogger.h"
#include "cpplog/LogLevel.h"

using namespace std;

int main() {
    try {
        cout << "Initializing example." << endl;

        cpplog::BaseLogger logger(cpplog::LogLevel::INFO);

        logger.debug("Hello World!");
        logger.info("Hello World!");
        logger.critical("Hello World!");
        logger.warning("Hello World!");
        logger.error("Hello World!");
        logger.critical("Hello World!");

        return 0;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
}
