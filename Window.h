#pragma once
#include "Redef.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <sstream>
#include <memory>
#include <optional>
#include <iostream>

struct Window {

	//registers and creates a window
	Window(int width, int height, const char* name);
	~Window();


	HINSTANCE getInstance();
	HWND WindowHandle();
	const char* getClassName();

	//return mouse and keyboard device interface
	Keyboard keyboard;
	Mouse mouse;
	//update mouse and keyboard states
	void Update() {
		keyboard.Update();
		mouse.Update();
	};

	//process messages
	static std::optional<int> ProcessMessages();

private:

	static constexpr const char* className = "Window32";
	HINSTANCE hInstance;
	HWND hWnd;

	//message relay to object
	//cannot pass member function instance as wndproc!
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

};

