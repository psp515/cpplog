//
// Created by psp515 on 02.03.2025.
//

#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>

using namespace std;

namespace clog {
    class ILogger {
    public:
        virtual ~ILogger() = default;

        virtual void debug(const string&) = 0;
        virtual void info(const string&) = 0;
        virtual void warning(const string&) = 0;
        virtual void error(const string&) = 0;
        virtual void critical(const string&) = 0;

    };
}

#endif //ILOGGER_H
