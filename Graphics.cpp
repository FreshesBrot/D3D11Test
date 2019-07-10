#include "Graphics.h"
#include "Redef.h"

Graphics::Graphics() { }

Graphics::Graphics(HWND hWnd) {

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
	GFX_FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	GFX_FAILED(device->CreateRenderTargetView(
		pBackBuffer.Get(), nullptr, &target
	));

	//specify viewport
	D3D11_VIEWPORT vp = {};
	vp.Height = 600;
	vp.Width = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftY = 0;
	vp.TopLeftX = 0;
	context->RSSetViewports(1u, &vp);

	//set up the Z-Buffer

	//create the depth stencil state and description
	wrl::ComPtr<ID3D11DepthStencilState> pDSstate;
	D3D11_DEPTH_STENCIL_DESC DSdesc = {};
	DSdesc.DepthEnable = TRUE;
	DSdesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DSdesc.DepthFunc = D3D11_COMPARISON_LESS;
	GFX_FAILED(device->CreateDepthStencilState(&DSdesc, &pDSstate));
	//bind to the output merger
	context->OMSetDepthStencilState(pDSstate.Get(), 0u);


	//create the texture 
	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	//texture description
	D3D11_TEXTURE2D_DESC Tdesc;
	Tdesc.Width = 600u;
	Tdesc.Height = 600u;
	Tdesc.MipLevels = 1u;
	Tdesc.ArraySize = 1u;
	Tdesc.Format = DXGI_FORMAT_D32_FLOAT;
	//used for anti-aliasing
	Tdesc.SampleDesc.Count = 1u;
	Tdesc.SampleDesc.Quality = 0u;

	Tdesc.Usage = D3D11_USAGE_DEFAULT;
	Tdesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	Tdesc.CPUAccessFlags = 0u;
	Tdesc.MiscFlags = 0u;


	GFX_FAILED(device->CreateTexture2D(&Tdesc, nullptr, &pDepthStencil));

	//create the view of the depth stencil
	//view description
	D3D11_DEPTH_STENCIL_VIEW_DESC DSVdesc = {};
	DSVdesc.Format = DXGI_FORMAT_D32_FLOAT;
	DSVdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DSVdesc.Texture2D.MipSlice = 0u;

	GFX_FAILED(device->CreateDepthStencilView(pDepthStencil.Get(), &DSVdesc, &depthStencil));

	//bind the render target and the depth stencil to the Output Merger
	context->OMSetRenderTargets(1u, target.GetAddressOf(), depthStencil.Get());

}

Graphics::~Graphics() {
	//assigning a nullptr to comPtr is equal to releasing it
	device = nullptr;
	context = nullptr;
	swapChain = nullptr;
	target = nullptr;
	depthStencil = nullptr;
}


void Graphics::ClearBuffer(float r, float g, float b) {
	if (r > 1.0f) r = 1.0f;
	if (g > 1.0f) g = 1.0f;
	if (b > 1.0f) b = 1.0f;

	//clear backbuffer
	const float color[] = { r,g,b,1.0f };
	context->ClearRenderTargetView(target.Get(), color);
	//clear depth stencil
	context->ClearDepthStencilView(depthStencil.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::DrawIndexed(int numIndices, int indexOffset, int baseVertexLocation) {
	context->DrawIndexed(numIndices, indexOffset, baseVertexLocation);
}

void Graphics::EndFrame() {
	HRESULT hr;
	if FAILED(hr = swapChain->Present(1u, 0u)) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			GFX_DEVICE_REMOVED(device->GetDeviceRemovedReason());
		GFX_FAILED(hr);
	}
}


