#pragma once
#include "Redef.h"
#include "Graphics.h"

struct Window {
	
	Window(int width, int height, const char* name) noexcept ;
	~Window();

	HINSTANCE getInstance();
	HWND WindowHandle();
	const char* getClassName();
	//return the graphics device interface
	Graphics Gfx();

private:
	
	Graphics gfx;
	static constexpr const char* className = "Window32";
	HINSTANCE hInstance;
	HWND hWnd;

};


