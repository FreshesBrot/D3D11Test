#include "PixelShader.h"

PixelShader::PixelShader(const wchar_t* fileName) {
	this->fileName = fileName;
}

PixelShader::~PixelShader() { }

void PixelShader::Bind() {
	HRESULT hr;

	wrl::ComPtr<ID3DBlob> pBlob;
	wrl::ComPtr<ID3D11PixelShader> pShader;
	//create shader object
	GFX_FAILED(D3DReadFileToBlob(fileName,&pBlob));
	GFX_FAILED(getDevice()->CreatePixelShader(
		pBlob->GetBufferPointer(), pBlob->GetBufferSize(),
		nullptr, &pShader
		));
	//bind shader
	getContext()->PSSetShader(pShader.Get(),nullptr,0);
}

void PixelShader::Update() { }

void PixelShader::Unbind() {
	this->~PixelShader();
}
