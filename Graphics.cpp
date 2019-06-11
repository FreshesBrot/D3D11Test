#include "Graphics.h"
#include "Redef.h"
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

//setup adapteres
Graphics::Graphics() : hWnd(nullptr) {

}

Graphics::~Graphics() {
	if (device != nullptr) 
		device->Release();

	if (context != nullptr)
		context->Release();
	if (swapChain != nullptr)
		swapChain->Release();
}

void Graphics::createDevice() {
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	HRESULT err = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&swapChain,
		&device,
		nullptr,
		&context
	);

}

void Graphics::setWndHandle(HWND hWnd) {
	this->hWnd = hWnd;
}

ID3D11Device* Graphics::Device() {
	return device;
}

ID3D11DeviceContext* Graphics::Context() {
	return context;
}

void Graphics::EndFrame() {
	swapChain->Present(2u, 0u);
}
