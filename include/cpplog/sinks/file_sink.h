//
// Created by psp515 on 09.03.2025.
//

#ifndef FILE_SINK_H
#define FILE_SINK_H

#include <mutex>
#include <utility>
#include <cpplog/sink.h>

namespace cpplog::sinks {
	class FileSink final : public Sink {
	public:
		explicit FileSink(string  filename) : filename(std::move(filename)) {}
		FileSink(const FileSink&) = delete;
		
		void log(const Log& log) const override;
	private:
		string filename;
		static std::mutex mtx;
	};
}

#endif //FILE_SINK_H
