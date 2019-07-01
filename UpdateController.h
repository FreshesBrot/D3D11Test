#pragma once
#include "Graphics.h"

//this class serves as a change-state observer between the graphics interface and the bindable objects
//all required changes are passed through this class which the bindable interface can access
class UpdateController {
public:
	UpdateController();
	~UpdateController();

	
	//set the objects
	void set(dx::XMMATRIX transform);
	void set(std::vector<Vertex> vertices);
	void set(std::vector<int> indices);
	void setPSState(int state);
	void setVSState(int state);
	void setTextureState(int state);

	//get the Objects
	dx::XMMATRIX getTransform();
	std::vector<Vertex> getNewVertices();
	std::vector<int> getNewIndices();
	int getVSState();
	int getPSState();
	int getTextureState();

	//set the projection matrix
	static void setProjectionMatrix(dx::XMMATRIX projectionMatrix);

	//projection matrix
	static dx::XMMATRIX m_projection;



private:

	//the objects that can change
	dx::XMMATRIX m_Transform;
	std::vector<Vertex> newVertices;
	std::vector<int> newIndices;
	int VSState;
	int PSState;
	int textureState;
};

