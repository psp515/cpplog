//
// Created by kolbe on 08.04.2025.
//

#ifndef LOGLEVEL_H
#define LOGLEVEL_H

namespace cpplog::common {

/** Enum representing levels of events possible to register.
*
*/
enum LogLevel {
	DEBUG = 0,
	INFO = 1,
	WARN = 2,
	ERROR = 3,
	CRITICAL = 4
};
}

#endif //LOGLEVEL_H
