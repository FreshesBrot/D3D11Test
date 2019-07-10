#pragma once
#include "Object.h"

//this class represents a cube
class Cube : public Object {
public:

	//initializes the cubes data
	Cube();

	std::vector<int> getIndices() override;
	std::vector<Vertex> getVertices() override;

	int getVSID() override;
	int getPSID() override;
	int getTXID() override;

	const wchar_t* getVSfileName() override;
	const wchar_t* getPSfileName() override;
	const wchar_t* getTXfileName() override;

private:

	//the objects geometry data
	std::vector<int> indices;
	std::vector<Vertex> vertices;
};

