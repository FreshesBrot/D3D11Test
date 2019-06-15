#include "Graphics.h"
#include "Redef.h"
#include "CustomException.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include "dxerr.h"
#include <sstream>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")


//graphics exception definition
Graphics::GraphicsException::GraphicsException(int line, const char* file, HRESULT hr) {
	iLine = line; iFile = file; errorCode = hr;
}

const char* Graphics::GraphicsException::what() const noexcept {
	std::ostringstream oss;
	oss <<"[CODE]: "<< (int) errorCode << "\n" <<
		"[LINE]: " << iLine << "\n" <<
		"[FILE]: " << iFile << "\n" <<
		Translate(errorCode);
	msgBuffer = oss.str();
	return msgBuffer.c_str();
}

const char* Graphics::GraphicsException::getType() const noexcept {
	return "GRAPHICS EXCEPTION";
}

Graphics::DeviceRemovedException::DeviceRemovedException(int line, const char* file, HRESULT hr) {
	iLine = line; iFile = file; errorCode = hr;
}

const char* Graphics::DeviceRemovedException::getType() const noexcept {
	return "DEVICE REMOVED EXCEPTION";
}

const char* Graphics::GraphicsException::Translate(HRESULT hr) const noexcept {
	char buffer[512];
	DXGetErrorDescription(hr, buffer, sizeof(buffer));
	std::ostringstream oss;
	oss << "[ERROR] " << DXGetErrorString(hr) << "\n[DESCRIPTION] " << buffer;
	codeBuffer = oss.str();
	return codeBuffer.c_str();
}

//throws exception if failed
#define GFX_FAILED(hrcall) if ( FAILED( hr = hrcall ) ) throw Graphics::GraphicsException(__LINE__,__FILE__,hr);
#define GFX_DEVICE_REMOVED(hr) Graphics::DeviceRemovedException(__LINE__,__FILE__,(hr));

//setup adapteres

Graphics::Graphics(HWND hWnd) : bufferColors({0,0,0}){

	//device initilization

	HRESULT hr;

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
	GFX_FAILED(D3D11CreateDeviceAndSwapChain(
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
	));
		
	//access to render target view
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	GFX_FAILED(swapChain.Get()->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	GFX_FAILED(device.Get()->CreateRenderTargetView(
		pBackBuffer.Get(), nullptr, &target
	))
	pBackBuffer = nullptr;

}

Graphics::~Graphics() {
	//assigning a nullptr to comPtr is equal to releasing it
	device = nullptr;
	context = nullptr;
	swapChain = nullptr;
	target = nullptr;
}


#pragma region buffers
void Graphics::ClearBuffer(float r, float g, float b) {
	if (r > 1.0f) r = 1.0f;
	if (g > 1.0f) g = 1.0f;
	if (b > 1.0f) b = 1.0f;
	
	bufferColors = { r,g,b };

	const float color[] = { r,g,b,1.0f };
	context.Get()->ClearRenderTargetView(target.Get(), color);
}

void Graphics::ClearBuffer() {
	const float color[] = { bufferColors.r,bufferColors.g,bufferColors.b,1.0f };
	context.Get()->ClearRenderTargetView(target.Get(), color);
}

void Graphics::setBufferColors(float r, float g, float b) {
	if (r > 1.0f) r = 1.0f;
	if (g > 1.0f) g = 1.0f;
	if (b > 1.0f) b = 1.0f;

	bufferColors = { r,g,b };
}

#pragma endregion

void Graphics::DrawTest() {

	//initializing the entire graphics pipeline 

	HRESULT hr;

	//vertex struct
	struct Vertex {
		struct {
			float x, y;
		} Pos;
		struct {
			float r, g, b;
		} Color;

	};

	//geometry data
	const Vertex vertices[] = {
		{0.0f,0.5f,1.0f,0.0f,0.0f},
		{0.5f,-0.5f,0.0f,1.0f,0.0f},
		{-0.5f,-0.5,0.0f,0.0f,1.0f}
	};

	//subresource data
	D3D11_SUBRESOURCE_DATA pData = {};
	pData.pSysMem = vertices;
	pData.SysMemPitch = 0u;
	pData.SysMemSlicePitch = 0u;
	
	//buffer description for vertices
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof( vertices );
	bd.StructureByteStride = sizeof( Vertex );

	//pointer to vertexbuffer
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;

	GFX_FAILED(device->CreateBuffer(&bd, &pData, &pVertexBuffer));
	
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	//set vertex buffer
	context->IASetVertexBuffers(0u,1u,pVertexBuffer.GetAddressOf(),&stride,&offset);
	
	//set vertex shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	GFX_FAILED(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));
	//create shader object
	GFX_FAILED(device->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));
	//bind shader to pipeline
	context->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	//set input layout
	wrl::ComPtr<ID3D11InputLayout> pInLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,8u,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	
	GFX_FAILED(device->CreateInputLayout(ied, 2u, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInLayout));

	context->IASetInputLayout(pInLayout.Get());

	//set pixel shader
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	//use blob from previous
	GFX_FAILED(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));
	//create shader object
	GFX_FAILED(device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
	//bind shader to pipeline
	context->PSSetShader(pPixelShader.Get(), nullptr, 0);




	//set primitve type
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//specify target view
	context->OMSetRenderTargets(1u, target.GetAddressOf(), nullptr);

	//specify viewport
	D3D11_VIEWPORT vp = {};
	vp.Height = 600;
	vp.Width = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftY = 0;
	vp.TopLeftX = 0;
	context->RSSetViewports(1u, &vp);

	//draw
	context->Draw((UINT) std::size(vertices), 0u);
}

void Graphics::EndFrame() {
	HRESULT hr;
	if FAILED(hr = swapChain->Present(1u, 0u)) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			throw GFX_DEVICE_REMOVED(device->GetDeviceRemovedReason());
		GFX_FAILED(hr);
	}
}


