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

	//the cubes geometry data
	const std::vector<int> indices;
	const std::vector<Vertex> vertices;


};

