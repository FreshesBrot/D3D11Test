#include "App.h"

App::App() : w(600,600,"MAMA"){ }

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


void App::DoFrame() {
	//clear the back buffer and set new color
	
	w.Gfx().setBufferColors(0.1f, 0.5f, 0.9f);
	w.Gfx().ClearBuffer();

	//if t is pressed, execute drawtest
	if(w.keyboard.isPressed('T'))
	w.Gfx().DrawTest();

	SetWindowText(w.WindowHandle(), "Window32");
	
	if (w.mouse.OnButtonDown(Mouse::Button::L)) {
		std::ostringstream oss;
		oss << "(" << w.mouse.xPos() << "," << w.mouse.yPos() << ")";
		std::string s = oss.str();
		SetWindowText(w.WindowHandle(), s.c_str());
	}
	
	//update keyboard and mouse
	w.Update();

	//present backbuffer
	w.Gfx().EndFrame();
}

