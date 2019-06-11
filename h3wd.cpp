#include <Windows.h>
#include <iostream>
#include <sstream>
#include "Window.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	Window w(600,600,"MAMA MIA");

	//message pump
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg); //"translates" messages
		DispatchMessage(&msg); //gives messages to the DefWindowProc

		w.Gfx().EndFrame();
	} //GetMessage (see msdn)

	UnregisterClass(w.getClassName(), hInstance);
	if (gResult == -1) return -1;
	else return msg.wParam;
	
	return 0;

}