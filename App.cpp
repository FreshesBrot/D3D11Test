#include "App.h"

App::App() : w(600, 600, "CubeBox"), GI(w.WindowHandle()) {

}

App::~App() { }


int App::Start() {

	GI.setBufferColors(0.1f, 0.2f, 0.9f);
	GI.addObject(new Cube());
	GI.addObject(new Cube());
	GI.addObject(new Pyramid());
	GI.getObjectAt(0)->translate(2, 1, 2);
	GI.Retexture(GI.getObjectAt(0), L"cock.jpg");
	GI.getObjectAt(1)->translate(-2, 1, 2);
	GI.getObjectAt(2)->translate(0, -2, 2);
	
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
		z++;
	}
	if (w.mouse.OnScrollUp()) {
		z--;
	}

	float move = 0.1f;

	Object* o0 = GI.getObjectAt(0);
	Object* o1 = GI.getObjectAt(1);
	Object* o2 = GI.getObjectAt(2);

	//move speed
	float ms = 0.04f;
	//move objects
	if (w.keyboard.isPressed('D')) {
		o0->translate(ms, 0.0f, 0.0f);
		o1->translate(ms, 0.0f, 0.0f);
		o2->translate(ms, 0.0f, 0.0f);
	}
	
	if (w.keyboard.isPressed('A')) {
		o0->translate(-ms, 0.0f, 0.0f);
		o1->translate(-ms, 0.0f, 0.0f);
		o2->translate(-ms, 0.0f, 0.0f);
	}

	if (w.keyboard.isPressed('W')) {
		o0->translate(0.0f, 0.0f, ms);
		o1->translate(0.0f, 0.0f, ms);
		o2->translate(0.0f, 0.0f, ms);
	}
	
	if (w.keyboard.isPressed('S')) {
		o0->translate(0.0f, 0.0f, -ms);
		o1->translate(0.0f, 0.0f, -ms);
		o2->translate(0.0f, 0.0f, -ms);
	}

	//auto rotation
	o0->rotate(0.03f,0.0f,0.02f);
	o1->rotate(0.02f, 0.01f, 0.0f);
	o2->rotate(0.0f, 0.03f, 0.0f);

	GI.Draw();

	//update keyboard and mouse
	w.Update();

}

