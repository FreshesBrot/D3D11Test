#pragma once
#include <fstream>
#include <istream>
#include <sstream>
#include <locale.h>
#include <codecvt>
#include "FileReaderException.h"
#define END_OF_FILE "0"


//this class represents an object that can read a file
class FileReader {
public:
		
	FileReader(const wchar_t* fileName);
	~FileReader();

	//initiates the file stream
	void Read();

	//returns the next line of the file
	//returns null if file is at the end
	std::string nextLine();
	
	//closes the file stream
	void Close();

protected:

	//conversion from wchar to char
	std::string toString(std::wstring ws);

	//the file stream the class operates on
	std::fstream fs;

	//name of the file
	const wchar_t* fileName;
	//storage for error messages
	std::string file;

};
