#include <Windows.h>
#include <iostream>
#include <sstream>
#include "App.h"
#include "CustomException.h"



int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	try {
		
		App().Start();

	} catch (CustomException e) {
		MessageBox(nullptr,e.what(),e.getType(),MB_OK | MB_ICONEXCLAMATION );
	}
	catch (std::exception& e) {
		MessageBox(nullptr, e.what(), "Exception occured", MB_OK | MB_ICONEXCLAMATION);
	}


}