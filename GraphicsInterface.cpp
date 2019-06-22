#include "GraphicsInterface.h"

GraphicsInterface::GraphicsInterface(HWND hWnd) : 
	gfx(hWnd), UC(), 
	m_buffer(dx::XMMATRIX()),
	objects(),bindables()
{
	
	colors = { 0,0,0 };

	Bindable::setUpdateController(UC);
	Bindable::setGraphicsDevice(gfx);

	//bind all components to the graphics pipeline
	bindables.push_back(new VertexShader(L"VertexShader.cso"));
	bindables.push_back(new PixelShader(L"PixelShader.cso"));
	bindables.push_back(new IndexBuffer(collectIndices()));
	bindables.push_back(new VertexBuffer(collectVertices()));

	//bind every resource
	for (Bindable* bind : bindables)
		bind->Bind();

	//bind the transform buffer
	m_buffer.Bind();

}

GraphicsInterface::~GraphicsInterface() {
	
	for (Bindable* bind: bindables) {
		delete bind;
	}
	
	for (Object* obj : objects) {
		delete obj;
	}

}

void GraphicsInterface::Draw(float x, float y, float z, float Xangle, float Yangle) {
	ClearBackBuffer();

	gfx.Draw(x,y,z,Xangle,Yangle,36);
	gfx.EndFrame();
}

void GraphicsInterface::Draw() {
	//clear the backbuffer
	ClearBackBuffer();

	int indexOffset = 0, vertexOffset = 0;

	for (Object* obj : objects) {
		//update the transformation matrix constant buffer per object
		UC.set(obj->getTransformMatrix());
		m_buffer.Update();
		
		//draw ONLY the current object from the vector
		int amtIndices = obj->getIndices().size(),amtVertices = obj->getVertices().size();
		
		gfx.DrawIndexed(amtIndices, indexOffset, vertexOffset);
		indexOffset += amtIndices; vertexOffset += amtVertices;
	}

	//present the backbuffer
	gfx.EndFrame();

}

void GraphicsInterface::setBufferColors(float r, float g, float b) {
	colors = {r,g,b};
}

Graphics GraphicsInterface::getGfx() {
	return gfx;
}

void GraphicsInterface::addObject(Object* o){
	objects.push_back(o);
	//set the new indices and vertices
	UC.set(collectVertices());
	UC.set(collectIndices());
	//signal that the states have changed
	UC.setState(VertexBuffer::ID, true);
	UC.setState(IndexBuffer::ID, true);
	//call update on all bindables
	Update();
}

Object* GraphicsInterface::getObjectAt(int index) {
	return objects[index];
}

void GraphicsInterface::Update() {
	for (int i = 0; i < bindables.size(); i++)
		bindables[i]->Update();
}

std::vector<int> GraphicsInterface::collectIndices() {
	if (objects.empty()) return std::vector<int>();
	std::vector<int> allIndices;
	int sum = 0;
	//get the total amount of indices to reserve
	for (Object* obj : objects) {
		sum += obj->getIndices().size();
	}
	//reserve the required space
	allIndices.reserve(sum);

	//insert everything into allIndices
	for (Object* obj : objects) {
		std::vector<int> indices = obj->getIndices();
		allIndices.insert(allIndices.end(),indices.begin(),indices.end());
	}

	return allIndices;
}

std::vector<Vertex> GraphicsInterface::collectVertices() {
	if (objects.empty()) return std::vector<Vertex>();
	std::vector<Vertex> allVertices;
	int sum = 0;
	//get the total amount of Vertices to reserve
	for (Object* obj : objects) {
		sum += obj->getVertices().size();
	}
	//reserve the required space
	allVertices.reserve(sum);

	//insert everything into allVertices
	for (Object* obj : objects) {
		std::vector<Vertex> vertices = obj->getVertices();
		allVertices.insert(allVertices.end(), vertices.begin(), vertices.end());
	}

	return allVertices;
}

void GraphicsInterface::ClearBackBuffer() {
	float r = colors.r, g = colors.g, b = colors.b;

	gfx.ClearBuffer(r,g,b);
}


