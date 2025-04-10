//
// Created by kolbe on 09.04.2025.
//

#ifndef LOGGER_OPTIONS_H
#define LOGGER_OPTIONS_H

namespace cpplog::common {
class LoggerOptions {
public:
	LoggerOptions() = default;

private:
	bool logAsJson = false;
	bool logThread = false;
	bool logFuncInfo = false;
};
}
#endif //LOGGER_OPTIONS_H
