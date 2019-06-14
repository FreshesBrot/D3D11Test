#include "App.h"

App::App() : w(600,600,"MAMA"){ }

App::~App() { }

//starts the application and sustains the application loop
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

//this function will do everything once per frame
void App::DoFrame() {
	//clear the back buffer and set new color
	w.Gfx().setBufferColors(0.1f, 0.2f, 0.5f);
	w.Gfx().ClearBuffer();

	//if t is pressed, execute drawtest
	if(w.keyboard.isPressed('T'))
	w.Gfx().DrawTest();
	
	if (w.keyboard.OnRelease('T'))
		SetWindowText(w.WindowHandle(), "Draw Successfull");

	//update keyboard and mouse
	w.keyboard.Update();
	//w.mouse.Update()

	//present backbuffer
	w.Gfx().EndFrame();
}

