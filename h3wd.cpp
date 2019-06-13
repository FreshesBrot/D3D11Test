#include <Windows.h>
#include <iostream>
#include <sstream>
#include "App.h"
#include "CustomException.h"



int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	try {

		App app;

		//message pump
		MSG msg;
		BOOL gResult;
		
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
			TranslateMessage(&msg); //"translates" messages
			DispatchMessage(&msg); //gives messages to the DefWindowProc
			
			//application loop
			app.DoFrame();
		
		} //GetMessage (see msdn)

		if (gResult == -1) return -1;
		else return msg.wParam;

		return 0;
	} catch (CustomException e) {
		MessageBox(nullptr,e.what(),e.getType(),MB_OK | MB_ICONEXCLAMATION );
	}
	catch (std::exception& e) {
		MessageBox(nullptr, e.what(), "Exception occured", MB_OK | MB_ICONEXCLAMATION);
	}


}