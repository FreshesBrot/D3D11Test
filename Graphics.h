#pragma once
#include <d3d11.h>
#include <wrl.h>

namespace wrl = Microsoft::WRL;

struct Graphics {
public:

	Graphics(HWND hWnd);
	~Graphics();
	
	wrl::ComPtr<ID3D11Device> Device();
	wrl::ComPtr<ID3D11DeviceContext> Context();
	void EndFrame();
	void ClearBuffer(float r, float g, float b);
	void ClearBuffer();
	void setBufferColors(float r, float g, float b);
	void DrawTest();

private:
	
	struct {
		float r, g, b;
	} bufferColors;


	HWND hWnd;
	wrl::ComPtr<ID3D11Device> device = nullptr;
	wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
	wrl::ComPtr<IDXGISwapChain> swapChain = nullptr;
	wrl::ComPtr<ID3D11RenderTargetView> target = nullptr;


};

