#pragma once
#include "Object.h"

//this class represents the camera of the scene


class Camera : public Object {
	using Object::getTransformMatrix;
	using Object::getIndices;
	using Object::getVertices;
public:

	//initializes the camera
	Camera();

	//a camera is abstract and has no geometry; will return nothing
	std::vector<int> getIndices() override;
	std::vector<Vertex> getVertices() override;

	//returns the VIEW TRANSFORMATION MATRIX and not the model transformation
	dx::XMMATRIX getTransformMatrix() override;

private:

};

