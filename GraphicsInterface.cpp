#include "GraphicsInterface.h"

GraphicsInterface::GraphicsInterface(HWND hWnd) : gfx(hWnd), controller() {
	colors = { 0,0,0 };

	Bindable::setUpdateController(controller);
}

GraphicsInterface::~GraphicsInterface() {
	std::vector<Bindable*>::iterator it;
	for (it = bindables.begin(); it < bindables.end(); it++) {
		delete *it;
	}
}

void GraphicsInterface::Draw(float x, float y, float z, float Xangle, float Yangle) {
	ClearBackBuffer();

	gfx.Draw(x,y,z,Xangle,Yangle);
	gfx.EndFrame();
}

void GraphicsInterface::setBufferColors(float r, float g, float b) {
	colors = {r,g,b};
}

Graphics GraphicsInterface::getGfx() {
	return gfx;
}

void GraphicsInterface::addBindable(Bindable *b) {
	bindables.push_back(b);
}

void GraphicsInterface::ClearBackBuffer() {
	float r = colors.r, g = colors.g, b = colors.b;

	gfx.ClearBuffer(r,g,b);
}

