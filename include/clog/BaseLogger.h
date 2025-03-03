//
// Created by psp515 on 02.03.2025.
//

#ifndef BASELOGGER_H
#define BASELOGGER_H

#include "ILogger.h"
#include "LogLevel.h"

using namespace std;

namespace clog {
    class BaseLogger : public ILogger {
    public:
        BaseLogger(LogLevel logLevel);
        void debug(const std::string& message) override;
        void info(const std::string& message) override;
        void warning(const std::string& message) override;
        void error(const std::string& message) override;
        void critical(const std::string& message) override;
    private:
        LogLevel logLevel;
    };
}

#endif //BASELOGGER_H
