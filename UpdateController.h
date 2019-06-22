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

	//checks wether the specified object has changed
	bool hasChanged(int i);

	//sets the state whether and object changed or not
	void setState(int i,bool state);

private:
	//the changed queue
	//0: Pixelshader - 1: Vertexshader - 2: Indexbuffer - 3: Vertexbuffer - 4: Constbuffer
	std::vector<bool> changes;

	//the objects that can change
	dx::XMMATRIX m_Transform;
	std::vector<Vertex> newVertices;
	std::vector<int> newIndices;
};

