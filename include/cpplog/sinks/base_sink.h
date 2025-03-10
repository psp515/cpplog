//
// Created by psp515 on 10.03.2025.
//

#ifndef BASE_SINK_H
#define BASE_SINK_H

#include <string>
#include <cpplog/sink.h>

using namespace cpplog;

namespace cpplog::sinks {

class BaseSink : public Sink {
public:
	BaseSink() = default;
	BaseSink(const BaseSink&) = delete;
	virtual ~BaseSink() = default;
	virtual void log(const Log& log) const = 0;
protected:
	string format_message(const Log& log) const;
};
}

#endif //BASE_SINK_H
