#pragma once
#include <exception>
#include <string>
#include "Redef.h"

class CustomException : public std::exception {
public:

	CustomException(int line, const char* file, HRESULT hr);
	CustomException();

	const char* what() const noexcept override;
	virtual const char* getType() const noexcept;
	virtual const char* Translate(HRESULT hr) const noexcept;

protected:
	//internal storage
	int iLine;
	const char* iFile;
	HRESULT errorCode;
	mutable std::string codeBuffer;
	mutable std::string msgBuffer;

};

