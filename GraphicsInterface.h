#pragma once
#include "Graphics.h"
#include "Objects.h"
#include "UpdateController.h"
#include "PipelineInterface.h"

//this class represents the interface for the user for drawcalls and pipeline adjustments
class GraphicsInterface {
public:

	GraphicsInterface(HWND hWnd);
	~GraphicsInterface();

	//draws all objects in the object vector; also clears the backbuffer and depth stencil
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

	//retextures an object
	void Retexture(Object* obj, const wchar_t* fileName);

	//sets new VSshader for object
	void VSReShader(Object* obj, const wchar_t* VSFileName);

	//sets new PSshader for object
	void PSReShader(Object* obj, const wchar_t* PSFileName);

	//adds a component to an object and creates the buffer if there is none
	void AddComponentToObject(Object* obj, Component* comp);

private:

	//resets color values for the backbuffer
	void ClearBackBuffer();

	//backbuffer colors
	struct {
		float r, g, b;
	} colors;



	//combines all indices
	std::vector<int> allIndices;

	//combines all vertices
	std::vector<Vertex> allVertices;

	//all objects
	std::vector<Object*> objects;

	//the camera object for the Scene
	Camera camera;

	//graphics object
	Graphics* gfx;

	//update controller
	UpdateController* UC;

	//pipeline interface
	PipelineInterface PI;

};

