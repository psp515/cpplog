//
// Created by psp515 on 09.03.2025.
//

#ifndef FILE_SINK_H
#define FILE_SINK_H

#include <mutex>
#include <cpplog/sink.h>
#include <cpplog/sinks/base_sink.h>

namespace cpplog::sinks {
	class FileSink final : public BaseSink {
	public:
		explicit FileSink(const string& filename);
		explicit FileSink(const string& filename, ios_base::openmode mode);
		FileSink(const FileSink&) = delete;
		~FileSink() override = default;

		void log(const Log& log) const override;
	private:
		string filename;
		static std::mutex mtx;
	};
}

#endif //FILE_SINK_H
