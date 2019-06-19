#include "App.h"

App::App() : w(600,600,"CubeBox"){ }

App::~App() { }


int App::Start() {
	
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
	//clear the back buffer and set new color
	w.Gfx().setBufferColors(0.1f, 0.2f, 0.5f);
	w.Gfx().ClearBuffer();

	if (w.mouse.OnScrollDown()) {
		if (z < 10.0f) z++;
	}
	if (w.mouse.OnScrollUp()) {
		if (z > 1.0f) z--;
	}

	w.Gfx().Draw(float(w.mouse.xPos()), float(w.mouse.yPos()), z , float(w.mouse.xPos()) / 200, float(w.mouse.yPos()) / -200);

	//update keyboard and mouse
	w.Update();

	//present backbuffer
	w.Gfx().EndFrame();
}

