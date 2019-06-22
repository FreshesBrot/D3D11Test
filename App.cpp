#include "App.h"

App::App() : w(600,600,"CubeBox"), GI(w.WindowHandle()) {
	
}

App::~App() { }


int App::Start() {
	
	GI.setBufferColors(0.1f, 0.2f, 0.9f);
	GI.addObject(new Cube());

	while (true) {
		//check if processmessages returns any value
		//only return value, if WM_QUIT was posted to the msg queue
		if (const auto ecode = Window::ProcessMessages())
			return *ecode;
		
		//if nothing or something other than WM_QUIT was posted, continue program
		DoFrame();
	}

}

float z = 4.0f;
void App::DoFrame() {

	if (w.mouse.OnScrollDown()) {
		if (z < 10.0f) z++;
	}
	if (w.mouse.OnScrollUp()) {
		if (z > 1.0f) z--;
	}

	GI.getObjectAt(0)->setTransform(float(w.mouse.xPos()), float(w.mouse.yPos()), z);

	GI.Draw(20,20,z,0,0);
	
	//update keyboard and mouse
	w.Update();

}

