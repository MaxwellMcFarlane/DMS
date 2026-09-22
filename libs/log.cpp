#include "log.h"

Log::Log() {
	open("dms.log");
}

Log::Log(const std::string& filePath) {
	open(filePath);
}

Log::~Log() {
	if (stream.is_open()) {
		stream.flush();
		stream.close();
	}
}

void Log::open(const std::string& filePath) {
	if (stream.is_open()) {
		stream.close();
	}

	path = filePath;
	stream.open(path.c_str(), std::ios::out | std::ios::app);
	if (!stream.is_open()) {
		// Fallback path to avoid losing logs when the requested path is invalid.
		path = "dms.log";
		stream.open(path.c_str(), std::ios::out | std::ios::app);
	}
}

void Log::truncate() {
	if (stream.is_open()) {
		stream.close();
	}
	stream.open(path.c_str(), std::ios::out | std::ios::trunc);
}

bool Log::isOpen() const {
	return stream.is_open();
}

void Log::flush() {
	if (stream.is_open()) {
		stream.flush();
	}
}

Log& Log::operator<<(std::ostream& (*manip)(std::ostream&)) {
	if (stream.is_open()) {
		manip(stream);
	}
	return *this;
}
