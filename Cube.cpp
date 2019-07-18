#include "Cube.h"

Cube::Cube() :
#pragma region GEOMETRY
	//defined in faces
	vertices({
		//x,y,z				r,g,b			xn,yn,zn			tx_u,tx_v
	//frontface
		{-1.0f,-1.0f,-1.0f,	1.0f,1.0f,1.0f,	-1.0f,-1.0f,-1.0f,	0,1},
		{-1.0f,+1.0f,-1.0f,	1.0f,0.0f,0.0f,	-1.0f,+1.0f,-1.0f,	0,0},
		{+1.0f,+1.0f,-1.0f,	0.0f,1.0f,0.0f,	+1.0f,+1.0f,-1.0f,	1,0},
		{+1.0f,-1.0f,-1.0f,	0.0f,0.0f,1.0f,	+1.0f,-1.0f,-1.0f,	1,1}, //3

	//rightface
		{+1.0f,-1.0f,-1.0f,	1.0f,1.0f,1.0f,	+1.0f,-1.0f,-1.0f,	0,1},
		{+1.0f,+1.0f,-1.0f,	1.0f,0.0f,0.0f,	+1.0f,+1.0f,-1.0f,	0,0},
		{+1.0f,+1.0f,+1.0f,	0.0f,1.0f,0.0f,	+1.0f,+1.0f,+1.0f,	1,0},
		{+1.0f,-1.0f,+1.0f,	0.0f,0.0f,1.0f,	+1.0f,-1.0f,+1.0f,	1,1}, //7

	//backface
		{+1.0f,-1.0f,+1.0f,	1.0f,1.0f,1.0f,	+1.0f,-1.0f,+1.0f,	0,1},
		{+1.0f,+1.0f,+1.0f,	1.0f,0.0f,0.0f,	+1.0f,+1.0f,+1.0f,	0,0},
		{-1.0f,+1.0f,+1.0f,	0.0f,1.0f,0.0f,	-1.0f,+1.0f,+1.0f,	1,0},
		{-1.0f,-1.0f,+1.0f,	0.0f,0.0f,1.0f,	-1.0f,-1.0f,+1.0f,	1,1}, //11

	//leftface
		{-1.0f,-1.0f,+1.0f,	1.0f,1.0f,1.0f,	-1.0f,-1.0f,+1.0f,	0,1},
		{-1.0f,+1.0f,+1.0f,	1.0f,0.0f,0.0f,	-1.0f,+1.0f,+1.0f,	0,0},
		{-1.0f,+1.0f,-1.0f,	0.0f,1.0f,0.0f,	-1.0f,+1.0f,-1.0f,	1,0},
		{-1.0f,-1.0f,-1.0f,	0.0f,0.0f,1.0f,	-1.0f,-1.0f,-1.0f,	1,1}, //15

	//topface
		{-1.0f,+1.0f,-1.0f,	1.0f,1.0f,1.0f,-1.0f,+1.0f,-1.0f,	0,1},
		{-1.0f,+1.0f,+1.0f,	1.0f,0.0f,0.0f,-1.0f,+1.0f,+1.0f,	0,0},
		{+1.0f,+1.0f,+1.0f,	0.0f,1.0f,0.0f,+1.0f,+1.0f,+1.0f,	1,0},
		{+1.0f,+1.0f,-1.0f,	0.0f,0.0f,1.0f,+1.0f,+1.0f,-1.0f,	1,1}, //19

	//bottomface
		{-1.0f,-1.0f,+1.0f,	1.0f,1.0f,1.0f,	-1.0f,-1.0f,+1.0f,	0,1},
		{-1.0f,-1.0f,-1.0f,	1.0f,0.0f,0.0f,	-1.0f,-1.0f,-1.0f,	0,0},
		{+1.0f,-1.0f,-1.0f,	0.0f,1.0f,0.0f,	+1.0f,-1.0f,-1.0f,	1,0},
		{+1.0f,-1.0f,+1.0f,	0.0f,0.0f,1.0f,	+1.0f,-1.0f,+1.0f,	1,1}, //23

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
		21,23,20,	21,22,23,

	})
#pragma endregion
{
	//set the file names for the shaders
	VSfileName = L"VertexShader.cso";
	PSfileName = L"PixelShader.cso";
	//set the file name for the texture
	TXfileName = L"Kappa.jpg";
}

int Cube::getPSID() {
	return PSID;
}

int Cube::getTXID() {
	return TXID;
}

int Cube::getVSID() {
	return VSID;
}

const wchar_t* Cube::getVSfileName() {
	return VSfileName;
}

const wchar_t* Cube::getPSfileName() {
	return PSfileName;
}

const wchar_t* Cube::getTXfileName() {
	return TXfileName;
}


std::vector<int> Cube::getIndices() {
	return indices;
}

std::vector<Vertex> Cube::getVertices() {
	return vertices;
}
