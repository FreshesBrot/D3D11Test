#pragma once
#include "Graphics.h"
#include "Bindable.h"


class GraphicsInterface {
public:

	GraphicsInterface(HWND hWnd);
	~GraphicsInterface();

	//clears the backbuffer and presents it to the rendertarget
	void Draw(float x, float y, float z, float Xangle, float Yangle);
	void setBufferColors(float r, float g, float b);

	//returns the pointer to the graphics object
	Graphics getGfx();

	//adds a bindable object to the interface
	void addBindable(Bindable *b);

private:

	//resets color values for the backbuffer
	void ClearBackBuffer();
	
	//set up the bindable once

	//backbuffer colors
	struct {
		float r, g, b;
	} colors;


	//object vector


	//bindable vector
	std::vector<Bindable*> bindables;

	//graphics object
	Graphics gfx;

	//update controller
	UpdateController controller;
};

