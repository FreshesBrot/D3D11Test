#pragma once
#include <d3d11.h>

struct Graphics {
public:

	Graphics();
	~Graphics();
	void setWndHandle(HWND hWnd);
	
	ID3D11Device* Device();
	ID3D11DeviceContext* Context();
	void EndFrame();
	void createDevice();

private:
	
	HWND hWnd;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;

};

