#include "Graphics.h"
#include "Redef.h"
#include "CustomException.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include "dxerr.h"
#include <sstream>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")



#pragma region GFXEXC
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

#pragma endregion

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

	//sets up the rest of the pipeline
	setUpPipeline();

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

void Graphics::setUpPipeline() {
	//initializing the entire graphics pipeline 

	HRESULT hr;


	//geometry data
	const Vertex vertices[] = {
		//x,y,z,r,g,b
		{-1.0f,-1.0f,-1.0f,0.0f,0.0f,0.0f},
		{1.0f,-1.0f,-1.0f,1.0f,0.0f,0.0f}, 
		{-1.0f,1.0f,-1.0f,0.0f,1.0f,0.0f}, 
		{1.0f,1.0f,-1.0f,0.0f,0.0f,1.0f}, 
		{-1.0f,-1.0f,1.0f,1.0f,1.0f,0.0f},
		{1.0f,-1.0f,1.0f,1.0f,0.0f,1.0f}, 
		{-1.0f,1.0f,1.0f,0.0f,1.0f,1.0f}, 
		{1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, 
	};

	//index data
	//you can pass a vector!
	const std::vector<int> indices({
		0,2,1, 2,3,1,
		1,3,5,	3,7,5,
		2,6,3,	3,6,7,
		4,5,7,	4,7,6,
		0,4,2,	2,4,6,
		0,1,4, 1,5,4
		});

	indexElements = indices.size();

	//vertex resource data
	D3D11_SUBRESOURCE_DATA pData = {};
	pData.pSysMem = vertices;
	pData.SysMemPitch = 0u;
	pData.SysMemSlicePitch = 0u;

	//vertex buffer description
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);

	//create and set vertex buffer
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	GFX_FAILED(device->CreateBuffer(&bd, &pData, &pVertexBuffer));
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	context->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);


	//index resource data
	D3D11_SUBRESOURCE_DATA pData2 = {};
	pData2.pSysMem = indices.data();
	pData2.SysMemPitch = 0u;
	pData2.SysMemSlicePitch = 0u;

	//index buffer description
	D3D11_BUFFER_DESC bd2 = {};
	bd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd2.Usage = D3D11_USAGE_DEFAULT;
	bd2.CPUAccessFlags = 0u;
	bd2.MiscFlags = 0u;
	bd2.ByteWidth = indices.size()*sizeof(int);
	bd2.StructureByteStride = sizeof(int);

	//create and set index buffer
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	GFX_FAILED(device->CreateBuffer(&bd2, &pData2, &pIndexBuffer));
	context->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);


	//create and set pixel shader
	wrl::ComPtr<ID3DBlob> pBlob;
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	//use blob from previous
	GFX_FAILED(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));
	//create shader object
	GFX_FAILED(device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
	//bind shader to pipeline
	context->PSSetShader(pPixelShader.Get(), nullptr, 0);


	//create set vertex shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	GFX_FAILED(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));
	//create shader object
	GFX_FAILED(device->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));
	//bind shader to pipeline
	context->VSSetShader(pVertexShader.Get(), nullptr, 0u);


	//create and set input layout for vertex struct
	wrl::ComPtr<ID3D11InputLayout> pInLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	
	GFX_FAILED(device->CreateInputLayout(ied, 2u, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInLayout));
	context->IASetInputLayout(pInLayout.Get());


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

}

void Graphics::Draw(float x,float y,float z, float Yangle, float Xangle) {
	HRESULT hr;
	
	//set and create constant buffer for shader side
	struct ConstBuffer {
		dx::XMMATRIX m_translate;
	};

	CD3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(dx::XMMATRIX);
	cbd.StructureByteStride = 0u;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;

	const ConstBuffer cb = {
		rotateX(Xangle) * rotateY(Yangle) * translate(x,y,z) * dx::XMMatrixPerspectiveLH(1.0f,1.0,0.5f,10.0f)
	};

	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	csd.SysMemPitch = 0u;
	csd.SysMemSlicePitch = 0u;

	wrl::ComPtr<ID3D11Buffer> pConstBuffer;
	GFX_FAILED(device->CreateBuffer(&cbd, &csd, &pConstBuffer));
	context->VSSetConstantBuffers(0u, 1u, pConstBuffer.GetAddressOf());
	
	//draw
	context->DrawIndexed(indexElements,0u,0u);
}

dx::XMMATRIX Graphics::translate(float xPos, float yPos,float zPos) {

	float newX = 0, newY = 0, newZ = 0;
	newX = xPos / 300 -1 ;
	newY = -(yPos / 300) + 1 ;
	
	return dx::XMMatrixTranslation(newX, newY, zPos);
}

dx::XMMATRIX Graphics::rotateY(float angle) {
	return dx::XMMatrixRotationY(angle);
}

dx::XMMATRIX Graphics::rotateX(float angle) {
	return dx::XMMatrixRotationX(angle);
}


void Graphics::EndFrame() {
	HRESULT hr;
	if FAILED(hr = swapChain->Present(1u, 0u)) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			throw GFX_DEVICE_REMOVED(device->GetDeviceRemovedReason());
		GFX_FAILED(hr);
	}
}


