#pragma once
#include <d3d11.h>
#include "CustomException.h"
#include "GFXExc.h"
#include <vector>
#include <wrl.h>
#include <DirectXMath.h>
#include "Vertex.h"


namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

class Graphics {
	
	//make bindable a friend class for private access
	friend class Bindable;

public:


	//creates the D3D11 Device , Context and SwapChain
	Graphics(HWND hWnd);
	~Graphics();
	
	//stander constructor; uninteresting
	Graphics();

	void EndFrame();
	//clears the buffer with specified colors
	void ClearBuffer(float r, float g, float b);

	//draws whatever is setup by the setup function (for now)
	void Draw(float x,float y, float z, float Xangle, float Yangle);

	//translation matrix
	dx::XMMATRIX translate(float xPos,float yPos,float zPos);

	//rotation matrix
	dx::XMMATRIX rotateY(float angle);
	dx::XMMATRIX rotateX(float angle);

private:

	//sets up graphics pipeline
	void setUpPipeline();
	int indexElements = 0;

	HWND hWnd;
	wrl::ComPtr<ID3D11Device> device = nullptr;
	wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
	wrl::ComPtr<IDXGISwapChain> swapChain = nullptr;
	wrl::ComPtr<ID3D11RenderTargetView> target = nullptr;

	
};

