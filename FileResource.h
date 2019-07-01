#pragma once
#include "Graphics.h"

//this interface represents bindables that are made from files
class FileResource {
public:

	//takes the name of the file and stores it
	FileResource(const wchar_t* fileName);

	//Creates the resource and saves neccessary pointers
	virtual void Create(ID3D11Device* device) = 0;

protected:

	const wchar_t* fileName;

};

