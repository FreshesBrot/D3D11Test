#include "Graphics.h"
#include "Redef.h"
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

//setup adapteres


Graphics::Graphics(HWND hWnd) {

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&swapChain,
		nullptr,
		&context
	);

}

Graphics::~Graphics() {
	if (device != nullptr) 
		device->Release();

	if (context != nullptr)
		context->Release();

	if (swapChain != nullptr)
		swapChain->Release();
}

void Graphics::DoFrame() {
	//actions during 1 frame
}

void Graphics::setWndHandle(HWND hWnd) {
	this->hWnd = hWnd;
}

wrl::ComPtr<ID3D11Device> Graphics::Device() {
	return device;
}

wrl::ComPtr<ID3D11DeviceContext> Graphics::Context() {
	return context;
}



void Graphics::EndFrame() {
	swapChain->Present(2u, 0u);
}
