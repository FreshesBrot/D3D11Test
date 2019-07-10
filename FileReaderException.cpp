#include "FileReaderException.h"

FileReaderException::FileReaderException(int line, const char* file, std::string message)  {
	iLine = line; iFile = file;
	errorMsg = message;
}

FileReaderException::~FileReaderException() {
}

const char* FileReaderException::what() const noexcept {
	std::ostringstream oss;
	oss << "[LINE]: " << iLine << "\n" <<
		"[FILE]: " << iFile << "\n" <<
		"[ERROR]: " << errorMsg;
	msgBuffer = oss.str();
	return msgBuffer.c_str();
}

const char* FileReaderException::getType() const noexcept {
	return "File Reader Exception";
}
