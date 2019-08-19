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
Transform* t3;

int App::Start() {

	GI.setBufferColors(0.1f, 0.2f, 0.9f);
	GI.addObject(empty = new Empty());
	GI.AddComponentToObject(empty, new Light());
	//mesh file 1
	const wchar_t* file1 = L"..\\TerrainGenerator\\out\\Terrain.sof";
	//mesh file 2
	const wchar_t* file2 = L"test.sof";
	//plane mesh (file 3)
	const wchar_t* file3 = L"plane.sof";
	GI.addObject(o0 = new Cube());
	//GI.addObject(o1 = new Mesh(MeshFile(file1)));
	
	//o0->GetComponent<Transform*>()->setScale(0,0,0);
	//t1->setScale(0.1f, 0.1f, 0.1f);
	
	
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
	t1 = o0->GetComponent<Transform*>();

	
	//move speed
	float ms = 40;
	////move objects
	if (w.keyboard.isPressed(SHIFT))
		ms /= 2;
	if (w.keyboard.isPressed('D')) {
	//	t0->translate(ms, 0, 0);
		t1->translate(ms,  0, 0);
	//	t2->translate(ms,  0, 0);
	}
	//
	if (w.keyboard.isPressed('A')) {
	//	t0->translate(-ms, 0.0f, 0.0f);
		t1->translate(-ms, 0.0f, 0.0f);
	//	t2->translate(-ms, 0.0f, 0.0f);
	}

	if (w.keyboard.isPressed('W')) {
	//	t0->translate(0.0f, 0.0f, ms);
		t1->translate(0.0f, 0.0f, ms);
	//	t2->translate(0.0f, 0.0f, ms);
	}
	//
	if (w.keyboard.isPressed('S')) {
	//	t0->translate(0.0f, 0.0f, -ms);
		t1->translate(0.0f, 0.0f, -ms);
	//	t2->translate(0.0f, 0.0f, -ms);
	}

	if (w.keyboard.isPressed('T')) 
		Time::deltaTime = 0;
	if (w.keyboard.OnRelease('T'))
		Time::deltaTime = prevTime;

	//auto rotation
	t1->rotate(0.0f, ms, 0.0f);

	GI.Draw();

	//update keyboard and mouse
	w.Update();

}

