#pragma once
#include "Redef.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <sstream>
#include <memory>

struct Window {
	
	Window(int width, int height, const char* name);
	~Window();

	HINSTANCE getInstance();
	HWND WindowHandle();
	const char* getClassName();
	//return the graphics device interface
	Graphics& Gfx();

	Keyboard keyboard;
	Mouse mouse;

private:

	std::unique_ptr<Graphics> pGfx;
	static constexpr const char* className = "Window32";
	HINSTANCE hInstance;
	HWND hWnd;

	//message relay to object
	//cannot pass member function instance as wndproc!
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

};

