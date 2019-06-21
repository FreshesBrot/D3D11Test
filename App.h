#pragma once
#include "Window.h"
#include "GraphicsInterface.h"

//this class represents the entire application as a top level interface
class App {
public:
	
	App();
	~App();
	
	//starts the application and sustains the application loop
	int Start();
	//does the entire app logic once per frame
	void DoFrame();

private:


	Window w;
	GraphicsInterface GI;
	

};

