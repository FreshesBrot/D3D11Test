#include "Pyramid.h"

Pyramid::Pyramid() :
	vertices({
		{-1.0f,-1.0f,-1.0f,0.0f,0.0f,1.0f},
		{1.0f,-1.0f,-1.0f,0.0f,1.0f,0.0f},
		{1.0f,-1.0f,1.0f,1.0f,0.0f,0.0f},
		{-1.0f,-1.0f,1.0f,0.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f,1.0f,1.0f,1.0f}
	}),
	indices({
		0,1,3,	1,2,3,
		4,1,0,
		4,2,1,
		4,3,2,
		4,0,3
	})
{
	//set shader file names
	VSfileName = L"testVrt.cso";
	PSfileName = L"testPxl.cso";

	//set texture file name
	TXTfileName = nullptr;
}

std::vector<int> Pyramid::getIndices() {
	return indices;
}

std::vector<Vertex> Pyramid::getVertices() {
	return vertices;
}

dx::XMMATRIX Pyramid::getTransformMatrix() {
	return (rotateXYZ(rotation.x,rotation.y,rotation.z)
		* scal(scaling.x, scaling.y, scaling.z) *
		trans(position.x, position.y, position.z));
}

int Pyramid::getShaderID() {
	return shaderID;
}

int Pyramid::getTextureID(){
	return textureID;
}

const wchar_t* Pyramid::getVSfileName() {
	return VSfileName;
}

const wchar_t* Pyramid::getPSfileName() {
	return PSfileName;
}

const wchar_t* Pyramid::getTXTfileName() {
	return TXTfileName;
}
