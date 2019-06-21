#pragma once
#include "Graphics.h"

//this class serves as a change-state observer between the graphics interface and the bindable objects
class UpdateController {
public:
	UpdateController();
	~UpdateController();

	
	//set the objects
	void set(dx::XMMATRIX transform);
	void set(std::vector<Vertex> vertices);
	void set(std::vector<int> indices);
	
	//get the Objects
	dx::XMMATRIX getTransform();
	std::vector<Vertex> getNewVertices();
	std::vector<int> getNewIndices();

private:
	//the objects that can change
	dx::XMMATRIX m_transform;
	std::vector<Vertex> newVertices;
	std::vector<int> newIndices;
};

