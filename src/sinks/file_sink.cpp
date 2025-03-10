//
// Created by psp515 on 09.03.2025.
//

#define LOG_FOLDER "logs"

#include "../extensions/level_extensions.h"
#include <cpplog/sinks/file_sink.h>
#include <fstream>
#include <ostream>
#include <filesystem>

using namespace std;
using namespace cpplog::sinks;
using namespace cpplog::extensions;

mutex FileSink::mtx;

FileSink::FileSink(const string& filename) : FileSink(filename, ios::app) {
}

FileSink::FileSink(const string& filename, ios::openmode mode = ios::app) {

	const filesystem::path dir(move(LOG_FOLDER));
	const auto exists = filesystem::is_directory(dir);

	if (!exists) {
		filesystem::create_directory(dir);
	}

	const filesystem::path file(move(filename));
	const filesystem::path full_path = dir / file;

	ofstream ofs(full_path, mode);
	ofs.close();

	this->filename = move(full_path.string());
}

void FileSink::log(const Log& log) const {
	const auto message = format_message(log);

	lock_guard lock{mtx};

	ofstream log_file(filename, ios_base::app);

	log_file << message << endl;

	log_file.close();
}
