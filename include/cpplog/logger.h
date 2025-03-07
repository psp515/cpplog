//
// Created by psp515 on 02.03.2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include "sinks/console_sink.h"


#include <format>
#include <memory>
#include <string>
#include <vector>
#include <cpplog/sink.h>
#include <cpplog/common/log.h>
#include <cpplog/common/level.h>

using namespace std;
using namespace cpplog::common;

namespace cpplog {
    class Logger {
    public:
        Logger(const level ignore_level) : ignore_level(ignore_level) {
            //TODO: aLLOW SINKS
            auto sink = make_unique<sinks::ConsoleSink>();
            sinks.push_back(std::move(sink));
        };
        Logger(const Logger&) = delete;
        virtual ~Logger() = default;

        // template<class... Args>
        // void debug(format_string<Args...> fmt, Args&&... args);

        void debug(const string& message) const;
        void info(const string& message) const;
        void warning(const string& message) const;
        void error(const string& message) const;
        void critical(const string& message) const;
    private:
        void log(level level, const string& message)const;
        void log(const Log& log)const;
        level ignore_level;
        vector<unique_ptr<Sink>> sinks;
    };
}

#endif //LOGGER_H
