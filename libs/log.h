// Simple stream-style logger wrapper built on top of the C++ standard library.
#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>

class Log {
public:
	Log();
	explicit Log(const std::string& filePath);
	~Log();

	void open(const std::string& filePath);
	void truncate();
	bool isOpen() const;
	void flush();

	template <typename T>
	Log& operator<<(const T& value) {
		if (stream.is_open()) {
			stream << value;
		}
		return *this;
	}

	Log& operator<<(std::ostream& (*manip)(std::ostream&));

private:
	std::ofstream stream;
	std::string path;
};

#endif // LOG_H
