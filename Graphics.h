#pragma once
#include <d3d11.h>
#include "CustomException.h"
#include <vector>
#include <wrl.h>
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

class Graphics {
public:

	//setup custom graphics exception
#pragma region GFX_EXC
	
	class GraphicsException : public CustomException {

		using CustomException::CustomException;
	public:
		GraphicsException(int line, const char* file, HRESULT hr);

		const char* what() const noexcept override;
		const char* getType() const noexcept override;
		const char* Translate(HRESULT hr) const noexcept override;

	};

	//special case exception
	class DeviceRemovedException : public GraphicsException {
	public:
		DeviceRemovedException(int line, const char* file, HRESULT hr);
		const char* getType() const noexcept override;
	};

#pragma endregion

	//creates the D3D11 Device , Context and SwapChain
	Graphics(HWND hWnd);
	~Graphics();
	
	void EndFrame();
	//clears the buffer with specified colors
	void ClearBuffer(float r, float g, float b);
	//clears the buffer with colors specified by setBufferColors
	void ClearBuffer();
	//sets the colors for the clearBuffer() call
	void setBufferColors(float r, float g, float b);
	//draws whatever is setup by the setup function (for now)
	void Draw(float x,float y);

	dx::XMMATRIX translate(float xPos,float yPos);

private:
	
	//vertex struct for management
	struct Vertex {
		struct {
			float x, y;
		} Pos;
		struct {
			float r, g, b;
		} Color;

	};

	//color buffer
	struct {
		float r, g, b;
	} bufferColors;

	//sets up graphics pipeline
	void setUpPipeline();
	int indexElements = 0;

	HWND hWnd;
	wrl::ComPtr<ID3D11Device> device = nullptr;
	wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
	wrl::ComPtr<IDXGISwapChain> swapChain = nullptr;
	wrl::ComPtr<ID3D11RenderTargetView> target = nullptr;

	
};

