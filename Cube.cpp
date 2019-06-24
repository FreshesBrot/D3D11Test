#include "Cube.h"

Cube::Cube() :
	indices({
		0,2,1, 2,3,1,
		1,3,5,	3,7,5,
		2,6,3,	3,6,7,
		4,5,7,	4,7,6,
		0,4,2,	2,4,6,
		0,1,4, 1,5,4
	}),
	vertices({
	//x,y,z,r,g,b
	{-1.0f,-1.0f,-1.0f,0.0f,0.0f,0.0f},
	{1.0f,-1.0f,-1.0f,1.0f,0.0f,0.0f},
	{-1.0f,1.0f,-1.0f,0.0f,1.0f,0.0f},
	{1.0f,1.0f,-1.0f,0.0f,0.0f,1.0f},
	{-1.0f,-1.0f,1.0f,1.0f,1.0f,0.0f},
	{1.0f,-1.0f,1.0f,1.0f,0.0f,1.0f},
	{-1.0f,1.0f,1.0f,0.0f,1.0f,1.0f},
	{1.0f,1.0f,1.0f,1.0f,1.0f,1.0f},
	}) 
{}

dx::XMMATRIX Cube::getTransformMatrix() {
	return (rotateX(rotation.x) * rotateY(rotation.y) * rotateZ(rotation.z) 
		* scal(scaling.x, scaling.y, scaling.z) * 
		trans(position.x, position.y, position.z)) 
		* m_projection;
}

std::vector<int> Cube::getIndices() {
	return indices;
}

std::vector<Vertex> Cube::getVertices() {
	return vertices;
}


