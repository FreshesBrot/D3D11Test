#pragma once
#include <exception>
#include <sstream>
#include <string>
#include "Redef.h"

//this class represents a custom exception
class CustomException : public std::exception {
public:

	CustomException(int line, const char* file, HRESULT hr);
	CustomException();

	//returns the error information
	const char* what() const noexcept override;
	//returns the error type
	virtual const char* getType() const noexcept;
	//translates the HR code
	virtual const char* Translate(HRESULT hr) const noexcept;

protected:
	//internal storage
	int iLine;
	const char* iFile;
	HRESULT errorCode;
	mutable std::string codeBuffer;
	mutable std::string msgBuffer;

};

