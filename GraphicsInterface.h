#pragma once
#include "Graphics.h"
#include "Bindable.h"
#include "Cube.h"

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

	//clears the backbuffer and presents it to the rendertarget (deprecated)
	void Draw(float x, float y, float z, float Xangle, float Yangle);
	
	//draws all objects in the object vector
	void Draw();

	void setBufferColors(float r, float g, float b);

	//returns the pointer to the graphics object
	Graphics getGfx();

	//adds an object to the draw pipe
	void addObject(Object* o);

	//returns the object by index
	Object* getObjectAt(int index);

private:

	//rolls through all bindables and calls update
	void Update();

	//returns all indices
	std::vector<int> collectIndices();

	//returns all vertices
	std::vector<Vertex> collectVertices();


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
	UpdateController UC;

	//class that holds the matrix buffer
	MatrixBuffer m_buffer;

};

