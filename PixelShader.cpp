#include "PixelShader.h"

PixelShader::PixelShader(const wchar_t* fileName) {
	this->fileName = fileName;
}

PixelShader::~PixelShader() {
	pShader = nullptr;
}

void PixelShader::Create(ID3D11Device* device) {
	HRESULT hr;

	wrl::ComPtr<ID3DBlob> pBlob;
	GFX_FAILED(D3DReadFileToBlob(fileName, &pBlob));

	GFX_FAILED(device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(),
		nullptr, &pShader));

}

ID3D11PixelShader* PixelShader::Get() {
	return pShader.Get();
}