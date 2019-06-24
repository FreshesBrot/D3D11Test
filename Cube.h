#pragma once
#include "Object.h"

//this class represents a cube
class Cube : public Object {
	using Object::getTransformMatrix;
public:

	//initializes the cubes data
	Cube();


	//returns geometry data
	std::vector<int> getIndices() override;
	std::vector<Vertex> getVertices() override;

	dx::XMMATRIX getTransformMatrix() override;

private:

	//the cubes geometry data
	std::vector<int> indices;
	std::vector<Vertex> vertices;


};

