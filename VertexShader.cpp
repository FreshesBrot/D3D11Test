#include "VertexShader.h"


VertexShader::VertexShader(const wchar_t* fileName) {
	this->fileName = fileName;
}

VertexShader::~VertexShader() {
	pShader = nullptr;
	pIL = nullptr;
}

void VertexShader::Create(ID3D11Device* device) {
	HRESULT hr;

	wrl::ComPtr<ID3DBlob> pBlob;
	GFX_FAILED(D3DReadFileToBlob(fileName, &pBlob));
	device->CreateVertexShader(pBlob->GetBufferPointer(),pBlob->GetBufferSize(),
		nullptr,&pShader);

	//create and set input layout
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	GFX_FAILED(device->CreateInputLayout(ied, 2u,
		pBlob->GetBufferPointer(), pBlob->GetBufferSize(),
		&pIL
	));

}

ID3D11VertexShader* VertexShader::Get() {
	return pShader.Get();
}

ID3D11InputLayout* VertexShader::GetIL() {
	return pIL.Get();
}
