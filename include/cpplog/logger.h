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
    class Logger final {
    public:
		explicit Logger(const level ignore_level) : ignore_level(ignore_level) {};

        Logger(const level ignore_level, vector<unique_ptr<Sink>> sinks)
            : ignore_level(ignore_level), sinks(move(sinks)) {};

        Logger(const Logger&) = delete;
        ~Logger() = default;


        template<class... Args>
        void debug(format_string<Args...> fmt, Args&&... args) {
            if (this->ignore_level > DEBUG)
                return;

            this->log(DEBUG, fmt, forward<Args>(args)...);
        }

        template<class... Args>
        void info(format_string<Args...> fmt, Args&&... args) {
            if (this->ignore_level > INFO)
                return;

            this->log(INFO, fmt, forward<Args>(args)...);
        }

        template<class... Args>
        void warning(format_string<Args...> fmt, Args&&... args) {
            if (this->ignore_level > WARNING)
                return;

            this->log(WARNING, fmt, forward<Args>(args)...);
        }

        template<class... Args>
        void error(format_string<Args...> fmt, Args&&... args) {
            if (this->ignore_level > ERROR)
                return;

            this->log(ERROR, fmt, forward<Args>(args)...);
        }

        template<class... Args>
        void critical(format_string<Args...> fmt, Args&&... args) {
            if (this->ignore_level > CRITICAL)
                return;

            this->log(CRITICAL, fmt, forward<Args>(args)...);
        }

        void debug(const string& message) const;
        void info(const string& message) const;
        void warning(const string& message) const;
        void error(const string& message) const;
        void critical(const string& message) const;

    private:
        void log(const Log& log) const;
        void log(level level, const string& message) const;

        template<class... Args>
        void log(const level level, const format_string<Args...> fmt, Args&&... args) const {
            this->log(level, format(fmt, forward<Args>(args)...));
        }

        level ignore_level;
        std::vector<std::unique_ptr<Sink>> sinks;
    };
}

#endif //LOGGER_H
