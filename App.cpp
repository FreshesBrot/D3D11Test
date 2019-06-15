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
	w.Gfx().setBufferColors(0.1f, 0.2f, 0.5f);
	w.Gfx().ClearBuffer();

	//if t is pressed, execute drawtest
	if(w.keyboard.isPressed('T'))
	w.Gfx().Draw();
	
	std::string s;
	if (w.keyboard.isPressed('T'))
		s = "Held";
	else if (w.keyboard.isLoose('T'))
		s = "Loose";

	SetWindowText(w.WindowHandle(), s.c_str());

	//update keyboard and mouse
	w.keyboard.Update();
	//w.mouse.Update()

	//present backbuffer
	w.Gfx().EndFrame();
}

