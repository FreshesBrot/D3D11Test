#include "Window.h"
#include <sstream>


Window::Window(int width, int height, const char* name) : hInstance(GetModuleHandle(nullptr)), keyboard(), mouse() {
	
	//RECT adjusts height and width for the client region only
	RECT rc = {};
	rc.left = 100;
	rc.right = width + rc.left;
	rc.top = 100;
	rc.bottom = height + rc.top;
	//adjusts the dimensions of the window
	AdjustWindowRect(&rc, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	WNDCLASSEX wc = { 0 };
	const char* wndName = "myMum";
	wc.cbSize = sizeof(wc); //bytesize of window; always sizeof(wc)
	wc.style = CS_OWNDC;	//window style; owndc = own device context for each window
	wc.lpfnWndProc = HandleMsgSetup; // longpointer to function (lpfn) of a window procedure; handles messages
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
		rc.right - rc.left, rc.bottom - rc.top,
		nullptr,
		nullptr,
		getInstance(),
		this
		);

	ShowWindow(hWnd, SW_SHOW);
	
	//create graphics object
	pGfx = std::make_unique<Graphics>(hWnd);

}


Window::~Window() {
	//unregister (delete) window
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

std::optional<int> Window::ProcessMessages() {
	MSG msg;
	
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		//check if last peeked message is a quit message
		if (msg.message == WM_QUIT)
			return msg.wParam;
	
		//if not, dispatch message
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//return nothing (emtpy optional) when there is no message
	return {};
	
}

#pragma region wndproc

//sets custom parameter to the hWnd to access window instance
LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_NCCREATE) {

		//extracts pointer to the createstruct from the createwindow msg
		//createstruct contains a lParam which is the custom lparam specified in the createwindow
		const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		//extract the pointer to the created window instance from
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		//store pointer to the window instance as user data on the hWnd
		SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//change the wndproc to the intendet function
		SetWindowLongPtrA(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		//forward message to window instance msg handler
		return pWnd->HandleMessage(hWnd, msg, wParam, lParam);

	}
	return DefWindowProcA(hWnd, msg, wParam, lParam);
}

//relay to the window instance wndproc
LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//extract the pointer to the window instance from user_data
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	//forward all received messages to the instanced wndproc
	return pWnd->HandleMessage(hWnd, msg, wParam, lParam);
}

//instanced wndproc
LRESULT Window::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_CLOSE: //WM_CLOSE; message that is called on X-ing the window
		PostQuitMessage(10); //posts WM_QUIT to the message queue
		break;
	case WM_KEYDOWN: //WN_KEYDOWN; message, when a key is pressed; key value stored in wParam (capital = non capital)
		keyboard.Press((char)wParam);
		break;
	case WM_KEYUP: //WM_KEYUP; message called when a key is released; key value stored in wParam (capital = non capital)
		keyboard.Release((char)wParam);
		break;
	case WM_LBUTTONDOWN: //WM_LBUTTONDOWN; message that is called when left mouse button is clicked
		const POINTS pt = MAKEPOINTS(lParam); //mouse location stored in lParam; MAKEPOINTS macro gives a POINTS obj. with x,y coords
		mouse.UpdatePosition(pt);
		std::ostringstream oss;
		oss << "(" << mouse.xPos() << "," << mouse.yPos() << ")";
		std::string s = oss.str();
		SetWindowText(hWnd, s.c_str());
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);

}

#pragma endregion
