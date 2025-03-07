//
// Created by psp515 on 02.03.2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <format>
#include <memory>
#include <string>
#include <vector>
#include <cpplog/sink.h>
#include <cpplog/common/log.h>
#include <cpplog/common/level.h>
#include <cpplog/sinks/console_sink.h>

using namespace std;
using namespace cpplog::common;
using namespace cpplog::sinks;

namespace cpplog {
    class Logger {
    public:
		explicit Logger(const level ignore_level) : ignore_level(ignore_level) {};

        Logger(const level ignore_level, vector<unique_ptr<Sink>> sinks)
            : ignore_level(ignore_level), sinks(move(sinks)) {};

        //Logger(const Logger&) = delete;
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
        std::vector<std::unique_ptr<Sink>> sinks;
    };
}

#endif //LOGGER_H
