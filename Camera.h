#pragma once
#include "Object.h"

//this class represents the camera of the scene


class Camera : public Object {
public:

	//initializes the camera
	Camera();

	//a camera is abstract and has no geometry; will return nothing
	std::vector<int> getIndices() override { return std::vector<int>(); };
	std::vector<Vertex> getVertices() override { return std::vector<Vertex>(); };

	//returns the view matrix for the camera
	dx::XMMATRIX ViewTransform();

	//these functions are unused for the camera
	int getVSID() override { return -1; };
	int getPSID() override { return -1; };
	int getTXID() override { return -1; };

	const wchar_t* getVSfileName() override { return nullptr; };
	const wchar_t* getPSfileName() override { return nullptr; };
	const wchar_t* getTXfileName() override { return nullptr; };

private:

};

