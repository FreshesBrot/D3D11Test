#pragma once
#include "Graphics.h"
#include "Bindable.h"
#include "Object.h"

#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstBuffer.h"

//this class represents the interface for the user for drawcalls and pipeline adjustments
class GraphicsInterface {
public:

	GraphicsInterface(HWND hWnd);
	~GraphicsInterface();

	//clears the backbuffer and presents it to the rendertarget
	void Draw(float x, float y, float z, float Xangle, float Yangle);
	
	//draws all objects in the object vector
	void Draw();

	void setBufferColors(float r, float g, float b);

	//returns the pointer to the graphics object
	Graphics getGfx();

	//adds a bindable object to the interface
	void addBindable(Bindable* b);

	//adds an object to the draw pipe
	void addObject(Object* o);

private:

	//returns the count of all indices


	//resets color values for the backbuffer
	void ClearBackBuffer();

	//backbuffer colors
	struct {
		float r, g, b;
	} colors;


	//object vector
	std::vector<Object*> objects;
	

	//bindable vector
	std::vector<Bindable*> bindables;

	//graphics object
	Graphics gfx;

	//update controller
	UpdateController controller;
};

