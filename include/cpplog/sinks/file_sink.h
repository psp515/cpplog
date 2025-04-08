//
// Created by psp515 on 09.03.2025.
//

#ifndef FILE_SINK_H
#define FILE_SINK_H

#define LOG_FOLDER "logs"

#include <cpplog/sink.h>
#include <fstream>
#include <mutex>

namespace cpplog::sinks {
class FileSink final : public Sink {
public:
	explicit FileSink(const string& filename);
	explicit FileSink(const string& filename, ios::openmode mode);
	FileSink(const FileSink&) = delete;
	~FileSink() override = default;

	void log(const Log& log) const override;

private:
	string filename;
	static std::mutex mtx;
};
} // namespace cpplog::sinks

#endif //FILE_SINK_H
