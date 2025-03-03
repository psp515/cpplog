//
// Created by psp515 on 02.03.2025.
//


#include <exception>
#include <iostream>
#include <ostream>

#include "ILogger.h"
#include "BaseLogger.h"
#include "LogLevel.h"

using namespace std;

int main() {
    try {
        cout << "Initializing example." << endl;

        clog::BaseLogger logger(clog::LogLevel::INFO);

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
