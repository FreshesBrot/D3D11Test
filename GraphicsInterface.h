#pragma once
#include "Graphics.h"
#include "Cube.h"
#include "UpdateController.h"
#include "PipelineInterface.h"

//this class represents the interface for the user for drawcalls and pipeline adjustments
class GraphicsInterface {
public:

	GraphicsInterface(HWND hWnd);
	~GraphicsInterface();

	//clears the backbuffer and presents it to the rendertarget (deprecated)
	void Draw(float x, float y, float z, float Xangle, float Yangle);
	
	//draws all objects in the object vector
	void Draw();

	void setBufferColors(float r, float g, float b);

	//returns the pointer to the graphics object
	Graphics* getGfx();

	//adds an object to the draw pipeline and updates geometry buffers
	void addObject(Object* o);
	//adds an objects but doesnt update geometry pipeline
	void addObjectGhost(Object* o);

	//updates geometry pipeline (for after addObjectGhost)
	void UpdateGeometry();

	//returns the object by index
	Object* getObjectAt(int index);

private:

	//resets color values for the backbuffer
	void ClearBackBuffer();

	//backbuffer colors
	struct {
		float r, g, b;
	} colors;



	//combines all object indices and stores them
	std::vector<int> allIndices;

	//returns all vertices
	std::vector<Vertex> allVertices;



	//graphics object
	Graphics* gfx;

	//update controller
	UpdateController* UC;
	
	//object vector
	std::vector<Object*> objects;

	//pipeline interface
	PipelineInterface PI;

};

