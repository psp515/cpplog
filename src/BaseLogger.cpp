//
// Created by psp515 on 02.03.2025.
//

#include <iostream>
#include <cpplog/BaseLogger.h>

using namespace std;

namespace cpplog {
    BaseLogger::BaseLogger(const LogLevel log_level) {
        this->logLevel = log_level;

        cout << "Logger Initialized" << endl;
    }


    void BaseLogger::debug(const string& message) {
        if (logLevel >= DEBUG) {
            cout << "[DEBUG]: " << message << endl;
        }
    }

    void BaseLogger::info(const string& message) {
        if (logLevel >= INFO) {
            cout << "[INFO]: " << message << endl;
        }
    }

    void BaseLogger::warning(const string& message) {
        if (logLevel >= WARNING) {
            cout << "[WARNING]: " << message << endl;
        }
    }

    void BaseLogger::error(const string& message) {
        if (logLevel >= ERROR) {
            cout << "[ERROR]: " << message << endl;
        }
    }

    void BaseLogger::critical(const string& message) {
        if (logLevel >= CRITICAL) {
            cout << "[CRITICAL]: " << message << endl;
        }
    }
}