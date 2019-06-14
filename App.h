#pragma once
#include "Window.h"

class App {
public:
	
	App();
	~App();
	
	int Start();
	void DoFrame();

private:

	Window w;

};

