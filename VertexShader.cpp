#include "VertexShader.h"


VertexShader::VertexShader(const wchar_t* fileName) { 
	this->fileName = fileName;
}

VertexShader::~VertexShader() {
	VSset = false;
	pVshader = nullptr;
	pVshaderBlob = nullptr;
}

void VertexShader::Bind() {
	if (VSset) return;
	VSset = true;

	HRESULT hr;

	//create and bind vertex shader to pipeline
	GFX_FAILED(D3DReadFileToBlob(fileName,&pVshaderBlob));
	GFX_FAILED(getDevice()->CreateVertexShader(
		pVshaderBlob->GetBufferPointer(),
		pVshaderBlob->GetBufferSize(),nullptr,
		&pVshader
		));

	getContext()->VSSetShader(pVshader.Get(),nullptr,0u);

}

void VertexShader::Update() {

}
