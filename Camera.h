#pragma once
#include "Object.h"

//this class represents the camera of the scene


class Camera : public Object {
public:

	//initializes the camera
	Camera();

	//a camera is abstract and has no geometry; will return nothing
	std::vector<int> getIndices() override;
	std::vector<Vertex> getVertices() override;

	//returns the VIEW TRANSFORMATION MATRIX and not the model transformation
	dx::XMMATRIX getTransformMatrix() override;

	//these functions are unused for the camera
	int getShaderID() override { return 0; }
	const wchar_t* getPSfileName() override { return nullptr; }
	const wchar_t* getVSfileName() override { return nullptr; }
	void setShaderID(int ID) override {}

private:

};

