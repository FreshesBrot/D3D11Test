#pragma once
#include "Object.h"

//this class represents a cube
class Cube : public Object {
#pragma region USAGES
	using Object::getIndices;
	using Object::getVertices;
	using Object::getTransformMatrix;
	using Object::translate;
	using Object::setTransform;
	using Object::rotate;
	using Object::setRotation;
	using Object::scale;
	using Object::setScale;
#pragma endregion
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

	//shortcuts
	dx::XMMATRIX trans(float xOffset, float yOffset, float zOffset);

	dx::XMMATRIX rotateX(float angle);
	dx::XMMATRIX rotateY(float angle);
	dx::XMMATRIX rotateZ(float angle);

	dx::XMMATRIX scal(float xScale, float yScale, float zScale);

};

