#pragma once
#include <d3d11.h>
#include <wrl.h>

namespace wrl = Microsoft::WRL;

struct Graphics {
public:

	Graphics(HWND hWnd);
	~Graphics();
	void setWndHandle(HWND hWnd);
	
	wrl::ComPtr<ID3D11Device> Device();
	wrl::ComPtr<ID3D11DeviceContext> Context();
	void EndFrame();
	void ClearBuffer(float r, float g, float b);

	void DrawTest();

private:
	
	HWND hWnd;
	wrl::ComPtr<ID3D11Device> device = nullptr;
	wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
	wrl::ComPtr<IDXGISwapChain> swapChain = nullptr;
	wrl::ComPtr<ID3D11RenderTargetView> target = nullptr;

};

