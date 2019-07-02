#include "Pyramid.h"

Pyramid::Pyramid() :
	vertices({
		//x,y,z				r,g,b			xn,yn,zn		tx_u,tx_v
		//base
		{-1.0f,-1.0f,-1.0f,	0.0f,0.0f,1.0f,	0.0f,-1.0f,0.0f, 0,1},
		{+1.0f,-1.0f,-1.0f,	0.0f,1.0f,0.0f,	0.0f,-1.0f,0.0f, 1,1},
		{+1.0f,-1.0f,+1.0f,	1.0f,0.0f,0.0f,	0.0f,-1.0f,0.0f, 1,0},
		{-1.0f,-1.0f,+1.0f,	0.0f,0.0f,0.0f,	0.0f,-1.0f,0.0f, 0,0}, //3

		//front
		{-1.0f,-1.0f,-1.0f,	1.0f,1.0f,1.0f,	0.0f,0.0f,-1.0f, 0,1},
		{+0.0f,+1.0f,+0.0f,	1.0f,1.0f,1.0f,	0.0f,0.0f,-1.0f, 0.55f,0},
		{+1.0f,-1.0f,-1.0f,	1.0f,1.0f,1.0f,	0.0f,0.0f,-1.0f, 1,1},		//6

		//right
		{+1.0f,-1.0f,-1.0f,	1.0f,1.0f,1.0f,	1.0f,0.0f,0.0f, 0,1},
		{+0.0f,+1.0f,+0.0f,	1.0f,1.0f,1.0f,	1.0f,0.0f,0.0f, 0.55f,0},
		{+1.0f,-1.0f,+1.0f,	1.0f,1.0f,1.0f,	1.0f,0.0f,0.0f, 1,1},		//9

		//back
		{+1.0f,-1.0f,+1.0f,	1.0f,1.0f,1.0f,	0.0f,0.0f,1.0f, 0,1},
		{+0.0f,+1.0f,+0.0f,	1.0f,1.0f,1.0f,	0.0f,0.0f,1.0f, 0.55f,0},
		{-1.0f,-1.0f,+1.0f,	1.0f,1.0f,1.0f,	0.0f,0.0f,1.0f, 1,1},		//12
		
		//left
		{-1.0f,-1.0f,+1.0f,	1.0f,1.0f,1.0f,	-1.0f,0.0f,0.0f, 0,1},
		{+0.0f,+1.0f,+0.0f,	1.0f,1.0f,1.0f,	-1.0f,0.0f,0.0f, 0.55f,0},
		{-1.0f,-1.0f,-1.0f,	1.0f,1.0f,1.0f,	-1.0f,0.0f,0.0f, 1,1},		//15

	}),
	indices({
		//base
		0,3,1,	1,2,3,

		//front
		4,5,6,

		//right
		7,8,9,

		//back
		10,11,12,

		//left
		13,14,15
	})
{
	//set shader file names
	VSfileName = nullptr;
	PSfileName = nullptr;

	//set texture file name
	TXfileName = nullptr;
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

int Pyramid::getVSID() {
	return VSID;
}

int Pyramid::getPSID() {
	return PSID;
}

int Pyramid::getTXID() {
	return TXID;
}

const wchar_t* Pyramid::getVSfileName() {
	return VSfileName;
}

const wchar_t* Pyramid::getPSfileName() {
	return PSfileName;
}

const wchar_t* Pyramid::getTXfileName() {
	return TXfileName;
}

