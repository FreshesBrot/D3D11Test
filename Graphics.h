#pragma once
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include "CustomException.h"
#include "GFXExc.h"
#include <vector>
#include <wrl.h>
#include <DirectXMath.h>
#include "Vertex.h"


namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

//this class represents the basic graphics device
class Graphics {
	friend class Bindable;
public:


	//creates the D3D11 Device , Context, SwapChain, RenderTargetView and DepthStencilView
	Graphics(HWND hWnd);
	~Graphics();
	
	//standard constructor
	Graphics();
	
	//presents the backbuffer to the render target, thus ending a frame
	void EndFrame();

	//clears the buffer with specified colors and clears the depth buffer
	void ClearBuffer(float r, float g, float b);

	//draw call for indexed drawing; must specify number of indices, index offset and base vertex location
	void DrawIndexed(int numIndices, int indexOffset, int baseVertexLocation);

private:

	//handle to the window that is drawn to
	HWND hWnd;
	//pointer storage
	wrl::ComPtr<ID3D11Device> device = nullptr;
	wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
	wrl::ComPtr<IDXGISwapChain> swapChain = nullptr;
	wrl::ComPtr<ID3D11RenderTargetView> target = nullptr;
	wrl::ComPtr<ID3D11DepthStencilView> depthStencil = nullptr;
};

