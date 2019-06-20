#include "PixelShader.h"

PixelShader::PixelShader(const wchar_t* fileName) {
	this->fileName = fileName;
}

PixelShader::~PixelShader() {
	pPshader = nullptr;
}

void PixelShader::Bind() {
	if (PSset) return;
	PSset = true;
	
	HRESULT hr;

	wrl::ComPtr<ID3DBlob> pBlob;
	GFX_FAILED(D3DReadFileToBlob(fileName,&pBlob));
	GFX_FAILED(getDevice()->CreatePixelShader(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(), nullptr, &pPshader
	));

	getContext()->PSSetShader(pPshader.Get(),nullptr,0u);


}

void PixelShader::Update() { }
