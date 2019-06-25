#pragma once
#include "Object.h"

//this class represents a cube
class Cube : public Object {
	using Object::getTransformMatrix;
	using Object::getIndices;
	using Object::getVertices;
public:

	//initializes the cubes data
	Cube();

	std::vector<int> getIndices() override;
	std::vector<Vertex> getVertices() override;

	dx::XMMATRIX getTransformMatrix() override;

private:

	//the cubes geometry data
	std::vector<int> indices;
	std::vector<Vertex> vertices;


};

