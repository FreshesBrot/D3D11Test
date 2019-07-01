#pragma once
#include "Object.h"
#include "Objects.h"

//this class represents a pyramid with 4 edges
class Pyramid : public Object {
public:

	//initialize vertices, indices
	Pyramid();

	std::vector<int> getIndices() override;
	std::vector<Vertex> getVertices() override;

	dx::XMMATRIX getTransformMatrix() override;

	int getVSID() override;
	int getPSID() override;
	int getTXID() override;

	const wchar_t* getVSfileName() override;
	const wchar_t* getPSfileName() override;
	const wchar_t* getTXfileName() override;

private:

	//geometry data
	const std::vector<int> indices;
	const std::vector<Vertex> vertices;

};

