#include "Graphics.h"
#include "Redef.h"
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

//setup adapteres


Graphics::Graphics(HWND hWnd) {

	//swap chain description
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

	//setting up
	if FAILED( D3D11CreateDeviceAndSwapChain(
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
	)) throw EXCEPTION_DEBUG_INFO();

}

Graphics::~Graphics() {
	device = nullptr;
	context = nullptr;
	swapChain = nullptr;
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
