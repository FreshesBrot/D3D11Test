#pragma once
#include "Object.h"

//this class represents an object with no geometric data
class Empty : public Object {
public:

	//initialize the empty object
	Empty();

	//an empty has no geometric data
	std::vector<int> getIndices() override { return std::vector<int>(); };
	std::vector<Vertex> getVertices() override { return std::vector<Vertex>(); };

	//these functions are unused for the empty
	int getVSID() override { return -1; };
	int getPSID() override { return -1; };
	int getTXID() override { return -1; };

	const wchar_t* getVSfileName() override { return nullptr; };
	const wchar_t* getPSfileName() override { return nullptr; };
	const wchar_t* getTXfileName() override { return nullptr; };

};

