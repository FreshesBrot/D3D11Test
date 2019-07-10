#include "FileReader.h"


FileReader::FileReader(const wchar_t* fileName) : fs() {
	this->fileName = fileName;
	file = toString(std::wstring(fileName));
}

FileReader::~FileReader() { 
	if (fs.is_open())
		fs.close();
}

void FileReader::Read() { 
	fs.open(fileName); 
}

std::string FileReader::nextLine() {
	std::string line;
	if (std::getline(fs, line))
		return line;
	return std::string(END_OF_FILE);
}

void FileReader::Close() {
	if (fs.is_open())
	fs.close();
}

std::string FileReader::toString(std::wstring ws) {
	return std::string(ws.begin(), ws.end());
}
