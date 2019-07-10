#pragma once
#include "CustomException.h"
#define READ_EXC(msg) FileReaderException(__LINE__,__FILE__,(msg));


//this class represents an exception that occurs during a file read
class FileReaderException : public CustomException {
public:

	FileReaderException(int line, const char* file, std::string message);
	~FileReaderException();

	const char* what() const noexcept override;
	const char* getType() const noexcept override;


private:
	int iLine;
	const char* iFile;
	std::string errorMsg;
	mutable std::string msgBuffer;
};

