#pragma once
#include "Window.h"

class App {
public:
	
	App();
	~App();
	
	//starts the application and sustains the application loop
	int Start();
	//this function will do everything once per frame
	void DoFrame();

private:

	Window w;

};

