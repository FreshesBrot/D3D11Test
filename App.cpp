#include "App.h"

App::App() : w(600, 600, "CubeBox"), GI(w.WindowHandle()) {

}

App::~App() { }


int App::Start() {

	GI.setBufferColors(0.1f, 0.2f, 0.9f);
	GI.addObject(new Cube());
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
		z++;
	}
	if (w.mouse.OnScrollUp()) {
		z--;
	}

	float move = 0.1f;

	if (w.keyboard.isPressed('W'))
		GI.getCamera()->translate(0.0f, move, 0.0f);
	if (w.keyboard.isPressed('S'))
		GI.getCamera()->translate(0.0f, -move, 0.0f);


	Object* o0 = GI.getObjectAt(0);
	Object* o1 = GI.getObjectAt(1);

	Position p0 = o0->getPosition();
	o0->setTransform(p0.x, p0.y, z);

	GI.Draw();

	//update keyboard and mouse
	w.Update();

}

