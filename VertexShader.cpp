#include "VertexShader.h"

VertexShader::VertexShader(const wchar_t* fileName) {
	this->fileName = fileName;
}

VertexShader::~VertexShader() {
	pShaderBlob = nullptr;
}

void VertexShader::Bind() {
	HRESULT hr;

	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	//create shader object
	GFX_FAILED(D3DReadFileToBlob(fileName,&pShaderBlob));
	GFX_FAILED(getDevice()->CreateVertexShader(
		pShaderBlob->GetBufferPointer(),pShaderBlob->GetBufferSize(),
		nullptr,&pVertexShader
		));
	//bind shader object
	getContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);

}

void VertexShader::Update() { }

void VertexShader::Unbind() {
	this->~VertexShader();
}
