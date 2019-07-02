#include "App.h"

App::App() : w(600, 600, "CubeBox"), GI(w.WindowHandle()) {

}

App::~App() { }


int App::Start() {

	GI.setBufferColors(0.1f, 0.2f, 0.9f);
	GI.addObject(new Cube());
	GI.addObject(new Cube());
	GI.addObject(new Pyramid());
	GI.getObjectAt(0)->setTransform(2, 1, 5);
	GI.Retexture(GI.getObjectAt(0), L"cock.jpg");
	GI.getObjectAt(1)->setTransform(-2, 1, 5);
	GI.getObjectAt(2)->setTransform(0, -2, 5);
	
	while (true) {
		//check if processmessages returns any value
		//only return value, if WM_QUIT was posted to the msg queue
		if (const auto ecode = Window::ProcessMessages())
			return *ecode;

		//if nothing or something other than WM_QUIT was posted, continue program
		DoFrame();
	}

}

float prevTime = Time::deltaTime;
float z = 4.0f;
void App::DoFrame() {

	if (w.mouse.OnScrollDown()) {
		z++;
	}
	if (w.mouse.OnScrollUp()) {
		z--;
	}

	Object* o0 = GI.getObjectAt(0);
	Object* o1 = GI.getObjectAt(1);
	Object* o2 = GI.getObjectAt(2);

	//move speed
	float ms = 40;
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

	if (w.keyboard.isPressed('T')) 
		Time::deltaTime = 0;
	if (w.keyboard.OnRelease('T'))
		Time::deltaTime =prevTime;

	//auto rotation
	o0->rotate(30,0.0f,20);
	o1->rotate(20, 10, 0.0f);
	o2->rotate(0.0f, 30, 0.0f);

	GI.Draw();

	//update keyboard and mouse
	w.Update();

}

