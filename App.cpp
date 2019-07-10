#include "App.h"

App::App() : w(600, 600, "CubeBox"), GI(w.WindowHandle()) {

}

App::~App() { }


//some variables
Object* empty;
Object* o0;
Object* o1;
Object* o2;
Object* o3;
Transform* t0;
Transform* t1;
Transform* t2;

int App::Start() {

	GI.setBufferColors(0.1f, 0.2f, 0.9f);
	GI.addObject(empty = new Empty());
	GI.AddComponentToObject(empty, new Light());
	GI.addObject(o0 = new Cube());
	//GI.PSReShader(o0, L"NormalShader.cso");
	GI.addObject(o1 = new Cube());
	GI.addObject(o2 = new Pyramid());
	GI.addObject(o3 = new Mesh(MeshFile(L"test.txt")));


	Transform* t0 = o0->GetComponent<Transform*>();
	Transform* t1 = o1->GetComponent<Transform*>();
	Transform* t2 = o2->GetComponent<Transform*>();
	
	t0->setTransform(2, 1, 7);
	GI.Retexture(o1, L"cock.jpg");
	t1->setTransform(-2, 1, 7);
	t2->setTransform(0, -2, 7);

	
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

	//retrieve object transforms
	Transform* t0 = o0->GetComponent<Transform*>();
	Transform* t1 = o1->GetComponent<Transform*>();
	Transform* t2 = o2->GetComponent<Transform*>();
	
	
	//move speed
	float ms = 40;
	//move objects
	if (w.keyboard.isPressed('D')) {
		t0->translate(ms, 0, 0);
		t1->translate(ms,  0, 0);
		t2->translate(ms,  0, 0);
	}
	
	if (w.keyboard.isPressed('A')) {
		t0->translate(-ms, 0.0f, 0.0f);
		t1->translate(-ms, 0.0f, 0.0f);
		t2->translate(-ms, 0.0f, 0.0f);
	}

	if (w.keyboard.isPressed('W')) {
		t0->translate(0.0f, 0.0f, ms);
		t1->translate(0.0f, 0.0f, ms);
		t2->translate(0.0f, 0.0f, ms);
	}
	
	if (w.keyboard.isPressed('S')) {
		t0->translate(0.0f, 0.0f, -ms);
		t1->translate(0.0f, 0.0f, -ms);
		t2->translate(0.0f, 0.0f, -ms);
	}

	if (w.keyboard.isPressed('T')) 
		Time::deltaTime = 0;
	if (w.keyboard.OnRelease('T'))
		Time::deltaTime =prevTime;

	//auto rotation
	t0->rotate(30.0f, 0.0f, 0.0f);
	t1->rotate(0.0f, 0.0f, 40.0f);
	t2->rotate(0.0f, 30.0f, 0.0f);

	GI.Draw();

	//update keyboard and mouse
	w.Update();

}

