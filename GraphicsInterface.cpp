#include "GraphicsInterface.h"

GraphicsInterface::GraphicsInterface(HWND hWnd) :
	PI(), objects(), allIndices(), allVertices(), camera() {

	//allocate heap memory for update controller and graphics device
	gfx = new Graphics(hWnd);
	UC = new UpdateController();

	//set some static variables for the graphics object
	Bindable::setGraphicsObject(gfx);
	Bindable::setUpdateController(UC);
	Bindable::setWorldProjection(Object::m_projection);

	colors = { 0,0,0 };

	//intialize default values for the shader state controller
	PI.initDefault();
	//bind the required components of the pipeline interface
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
		//set view matrix for transform component
		Component::UpdateView(camera.ViewTransform());
		
		//update components
		PI.UpdateComponentBuffers(obj);

		//update shaderstate controller
		UC->setVSState(obj->getVSID());
		UC->setPSState(obj->getPSID());
		UC->setTextureState(obj->getTXID());

		PI.UpdateShaderState();

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

void GraphicsInterface::addObjectGhost(Object* o) {
	//push the new object
	objects.push_back(o);

	//insert new indices and vertices
	std::vector<int> objInd = o->getIndices();
	allIndices.insert(allIndices.end(), objInd.begin(), objInd.end());

	std::vector<Vertex> objVrt = o->getVertices();
	allVertices.insert(allVertices.end(), objVrt.begin(), objVrt.end());

	//set the states for the object
	int ID;
	ID = PI.addVertexShader(o->getVSfileName());
	o->setVSID(ID);
	ID = PI.addPixelShader(o->getPSfileName());
	o->setPSID(ID);
	ID = PI.addTexture(o->getTXfileName());
	o->setTXID(ID);

	//bind all components once
	PI.CreateComponentBuffers(o);

}

void GraphicsInterface::addObject(Object* o) {
	addObjectGhost(o);

	//update the update controller
	UC->set(allIndices); UC->set(allVertices);

	//call update on geometry buffers
	PI.UpdateGeometry();

}

void GraphicsInterface::UpdateGeometry() {
	//update the update controller
	UC->set(allIndices); UC->set(allVertices);

	PI.UpdateGeometry();
}

Object* GraphicsInterface::getObjectAt(int index) {
	return objects[index];
}

void GraphicsInterface::Retexture(Object* obj, const wchar_t* fileName) {
	int ID = PI.addTexture(fileName);
	obj->setTXID(ID);
	obj->setTXfile(fileName);
}

void GraphicsInterface::ClearBackBuffer() {
	float r = colors.r, g = colors.g, b = colors.b;

	gfx->ClearBuffer(r, g, b);
}


