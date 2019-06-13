#include "Window.h"
#include <sstream>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_CLOSE: //WM_CLOSE; message that is called on X-ing the window
		PostQuitMessage(0); //posts WM_QUIT to the message queue
		break;
	case WM_KEYDOWN: //WN_KEYDOWN; message, when a key is pressed; key value stored in wParam (capital = non capital)
		Window::getKeyboard().Press((char)wParam);
		if (Window::getKeyboard().isPressed('T'))
		SetWindowText(hWnd, "DDD");
		break;
	case WM_KEYUP: //WM_KEYUP; message called when a key is released; key value stored in wParam (capital = non capital)
		Window::getKeyboard().Release((char)wParam);
		break;
	case WM_LBUTTONDOWN: //WM_LBUTTONDOWN; message that is called when left mouse button is clicked
		const POINTS pt = MAKEPOINTS(lParam); //mouse location stored in lParam; MAKEPOINTS macro gives a POINTS obj. with x,y coords
		std::stringstream stream;
		stream << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hWnd, stream.str().c_str());

		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);

}


Keyboard Window::keyboard;

//register and create a window
Window::Window(int width, int height, const char* name) : hInstance(GetModuleHandle(nullptr)) {
	
	WNDCLASSEX wc = { 0 };
	const char* wndName = "myMum";
	wc.cbSize = sizeof(wc); //bytesize of window; always sizeof(wc)
	wc.style = CS_OWNDC;	//window style; owndc = own device context for each window
	wc.lpfnWndProc = WndProc; // longpointer to function (lpfn) of a window procedure; handles messages
	wc.cbClsExtra = 0; //uninteresting
	wc.cbWndExtra = 0; //unintereseting
	wc.hInstance = getInstance(); //handle to the "parent window"; main-instance for "main window"
	wc.hIcon = nullptr; //icon of the window; nullptr for default
	wc.hCursor = nullptr; //cursor of the window; nullptr for default
	wc.hbrBackground = nullptr; //sets the color of the background; nullptr for no draw calls
	wc.lpszMenuName = nullptr; //menu(?)
	wc.lpszClassName = getClassName(); //class name; typedef const char* LPCSTR == long pointer to c-string
	wc.hIconSm = nullptr; //small icon(?); nullptr for default
	RegisterClassEx(&wc);
	hWnd = CreateWindowA(
		getClassName(),
		name,
		WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200,
		width, height,
		nullptr,
		nullptr,
		getInstance(),
		nullptr
		);

	ShowWindow(hWnd, SW_SHOW);
	
	//create graphics object
	pGfx = std::make_unique<Graphics>(hWnd);



}

//unregister (delete) window
Window::~Window() {
	UnregisterClass(getClassName(), getInstance());
}

HINSTANCE Window::getInstance() {
	return hInstance;
}

HWND Window::WindowHandle() {
	return hWnd;
}

const char* Window::getClassName() {
	return className;
}

Graphics& Window::Gfx() {
	return *pGfx;
}

Keyboard Window::getKeyboard() {
	return keyboard;
}

