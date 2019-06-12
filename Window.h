#pragma once
#include "Redef.h"
#include "Graphics.h"
#include <memory>

struct Window {
	
	Window(int width, int height, const char* name);
	~Window();

	HINSTANCE getInstance();
	HWND WindowHandle();
	const char* getClassName();
	//return the graphics device interface
	Graphics& Gfx();

private:

	std::unique_ptr<Graphics> pGfx;
	static constexpr const char* className = "Window32";
	HINSTANCE hInstance;
	HWND hWnd;

};


