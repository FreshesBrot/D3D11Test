#include "GraphicsInterface.h"

GraphicsInterface::GraphicsInterface(HWND hWnd) :
	PI(), objects(), allIndices(), allVertices(), camera() {

	//allocate heap memory for update controller and graphics device
	gfx = new Graphics(hWnd);
	UC = new UpdateController();

	//set the graphics object for the bindables
	Bindable::setGraphicsObject(gfx);
	Bindable::setUpdateController(UC);

	colors = { 0,0,0 };

	//bind the components of the pipeline interface
	PI.BindComponents();

}

GraphicsInterface::~GraphicsInterface() {

	for (Object* obj : objects) {
		delete obj;
	}

	delete gfx;
	delete UC;
}

void GraphicsInterface::Draw() {
	//clear the backbuffer
	ClearBackBuffer();

	int indexOffset = 0, vertexOffset = 0;

	for (Object* obj : objects) {
		//calculate model transformation matrix
		dx::XMMATRIX modelTransform = obj->getTransformMatrix();
		//calculate model view transformation matrix
		dx::XMMATRIX modelViewTransform =  camera.getTransformMatrix() * modelTransform;
		//project the vertices on NDC
		dx::XMMATRIX projectedMVT = modelViewTransform * Object::m_projection;
		//update the controller with modelview matrix
		
		dx::XMMATRIX test =  obj->getTransformMatrix() * camera.getTransformMatrix() * Object::m_projection;
		UC->set(test);
		PI.UpdateTransformBuffer();
		//draw the object
		//store of indices and vertices
		int ind = obj->getIndices().size(), vrt = obj->getVertices().size();
		gfx->DrawIndexed(ind, indexOffset, vertexOffset);
		//update offsets
		indexOffset += ind;
		vertexOffset += vrt;
	}

	//end the frame 
	gfx->EndFrame();
}

void GraphicsInterface::setBufferColors(float r, float g, float b) {
	colors = { r,g,b };
}

Graphics* GraphicsInterface::getGfx() {
	return gfx;
}

void GraphicsInterface::addObject(Object* o) {
	//push the new object
	objects.push_back(o);

	//insert new indices and vertices
	std::vector<int> objInd = o->getIndices();
	allIndices.insert(allIndices.end(), objInd.begin(), objInd.end());

	std::vector<Vertex> objVrt = o->getVertices();
	allVertices.insert(allVertices.end(), objVrt.begin(), objVrt.end());

	//update the update controller
	UC->set(allIndices); UC->set(allVertices);

	//call update on geometry buffers
	PI.UpdateGeometry();

}

void GraphicsInterface::addObjectGhost(Object* o) {
	//push the new object
	objects.push_back(o);

	//insert new indices and vertices
	std::vector<int> objInd = o->getIndices();
	allIndices.insert(allIndices.end(), objInd.begin(), objInd.end());

	std::vector<Vertex> objVrt = o->getVertices();
	allVertices.insert(allVertices.end(), objVrt.begin(), objVrt.end());

}

void GraphicsInterface::UpdateGeometry() {
	//update the update controller
	UC->set(allIndices); UC->set(allVertices);

	PI.UpdateGeometry();
}

Object* GraphicsInterface::getObjectAt(int index) {
	return objects[index];
}

Camera* GraphicsInterface::getCamera() {
	return &camera;
}

void GraphicsInterface::ClearBackBuffer() {
	float r = colors.r, g = colors.g, b = colors.b;

	gfx->ClearBuffer(r, g, b);
}


