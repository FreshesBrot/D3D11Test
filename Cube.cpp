#include "Cube.h"

Cube::Cube() :
	//defined in faces
	vertices({
	//x,y,z,r,g,b,xn,yn,zn,tx_u,tx_v
	//frontface
		{-1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f},
		{-1.0f,1.0f,-1.0f,1.0f,0.0f,0.0f},
		{1.0f,1.0f,-1.0f,0.0f,1.0f,0.0f},
		{1.0f,-1.0f,-1.0f,0.0f,0.0f,1.0f}, //3

	//rightface
		{1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f},
		{1.0f,1.0f,-1.0f,1.0f,0.0f,0.0f},
		{1.0f,1.0f,1.0f,0.0f,1.0f,0.0f},
		{1.0f,-1.0f,1.0f,0.0f,0.0f,1.0f}, //7

	//backface
		{1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f,1.0f,0.0f,0.0f},
		{-1.0f,1.0f,1.0f,0.0f,1.0f,0.0f},
		{-1.0f,-1.0f,1.0f,0.0f,0.0f,1.0f}, //11

	//leftface
		{-1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f},
		{-1.0f,1.0f,1.0f,1.0f,0.0f,0.0f},
		{-1.0f,1.0f,-1.0f,0.0f,1.0f,0.0f},
		{-1.0f,-1.0f,-1.0f,0.0f,0.0f,1.0f}, //15

	//topface
		{-1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f},
		{-1.0f,1.0f,1.0f,1.0f,0.0f,0.0f},
		{1.0f,1.0f,1.0f,0.0f,1.0f,0.0f},
		{1.0f,1.0f,-1.0f,0.0f,0.0f,1.0f}, //19

	//bottomface
		{-1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f},
		{-1.0f,-1.0f,1.0f,1.0f,0.0f,0.0f},
		{1.0f,-1.0f,1.0f,0.0f,1.0f,0.0f},
		{1.0f,-1.0f,-1.0f,0.0f,0.0f,1.0f}, //23

		}),

	indices({
		//front
		1,3,0,	1,2,3,	

		//right
		5,7,4,	5,6,7,

		//back
		9,11,8,	9,10,11,

		//left
		13,15,12,	13,14,15,

		//top
		17,19,16,	17,18,19,

		//bottom
		20,23,21,	23,22,21,

	})
{
//set the file names for the shaders
	VSfileName = L"PixelShader.cso";
	PSfileName = L"VertexShader.cso";
}

dx::XMMATRIX Cube::getTransformMatrix() {
	return (rotateXYZ(rotation.x,rotation.y,rotation.z)
		* scal(scaling.x, scaling.y, scaling.z) *
		trans(position.x, position.y, position.z));
}

int Cube::getShaderID() {
	return shaderID;
}

void Cube::setShaderID(int ID) {
	if (!IDset) {
		shaderID = ID;
		IDset = true;
	}
}

const wchar_t* Cube::getVSfileName() {
	return VSfileName;
}

const wchar_t* Cube::getPSfileName() {
	return PSfileName;
}

std::vector<int> Cube::getIndices() {
	return indices;
}

std::vector<Vertex> Cube::getVertices() {
	return vertices;
}
