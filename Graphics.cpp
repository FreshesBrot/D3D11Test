#include "Graphics.h"
#include "Redef.h"
#include "CustomException.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

//throw some exceptions
#define CUSTOM_EXC(hr)(CustomException(__LINE__,__FILE__,hr));

//setup adapteres

//device initilization
Graphics::Graphics(HWND hWnd) {

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
	if FAILED( hr = D3D11CreateDeviceAndSwapChain(
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
	)) throw CUSTOM_EXC(hr);

	//access to render target view
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	if FAILED(hr = swapChain.Get()->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer)) throw CUSTOM_EXC(hr);
	if FAILED(hr = device.Get()->CreateRenderTargetView(
		pBackBuffer.Get(), nullptr, &target
	)) throw CUSTOM_EXC(hr);
	pBackBuffer = nullptr;

}

Graphics::~Graphics() {
	//assigning a nullptr to comPtr is equal to releasing it
	device = nullptr;
	context = nullptr;
	swapChain = nullptr;
	target = nullptr;
}

wrl::ComPtr<ID3D11Device> Graphics::Device() {
	return device;
}

wrl::ComPtr<ID3D11DeviceContext> Graphics::Context() {
	return context;
}

void Graphics::ClearBuffer(float r, float g, float b) {
	if (r > 1.0f) r = 1.0f;
	if (g > 1.0f) g = 1.0f;
	if (b > 1.0f) b = 1.0f;

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

//drawing test
//initializing graphics pipeline 
void Graphics::DrawTest() {

	HRESULT hr;

	//vertex struct
	struct Vertex {
		struct {
			float x, y;
		} Pos;

	};

	//geometry data
	const Vertex vertices[] = {
		{0.0f,0.5f},
		{0.5f,-0.5f},
		{-0.5f,-0.5}
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

	if FAILED(hr = device->CreateBuffer(&bd,&pData,&pVertexBuffer)) throw CUSTOM_EXC(hr);
	
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	//set vertex buffer
	context->IASetVertexBuffers(0u,1u,pVertexBuffer.GetAddressOf(),&stride,&offset);
	
	//set vertex shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	if FAILED(hr = D3DReadFileToBlob(L"VertexShader.cso", &pBlob))throw CUSTOM_EXC(hr);
	//create shader object
	if FAILED(hr = device->CreateVertexShader(pBlob->GetBufferPointer(),pBlob->GetBufferSize(),nullptr,&pVertexShader))throw CUSTOM_EXC(hr);
	//bind shader to pipeline
	context->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	//set input layout
	wrl::ComPtr<ID3D11InputLayout> pInLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	device->CreateInputLayout(ied, 1u, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInLayout);

	context->IASetInputLayout(pInLayout.Get());

	//set pixel shader
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	//use blob from previous
	if FAILED(hr = D3DReadFileToBlob(L"PixelShader.cso",&pBlob)) throw CUSTOM_EXC(hr);
	//create shader object
	if FAILED(device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader))throw CUSTOM_EXC(hr);
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
	swapChain->Present(1u, 0u);
}


