#include "App.h"

App::App() : w(600,600,"MAMA"){

}

App::~App() { }

//this function will do everything once per frame
void App::DoFrame() {
	//clear the back buffer and set new color
	w.Gfx().setBufferColors(0.1f, 0.2f, 0.5f);
	w.Gfx().ClearBuffer();

	//if t is pressed, execute drawtest
	bool b;
	if(b=w.getKeyboard().isPressed('T'))
	w.Gfx().DrawTest();
	
	if (w.getKeyboard().OnRelease('t'))
		SetWindowText(w.WindowHandle(), "Draw Successfull");


	//present backbuffer
	w.Gfx().EndFrame();
}

