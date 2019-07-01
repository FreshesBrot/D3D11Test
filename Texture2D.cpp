#include "Texture2D.h"

Texture2D::Texture2D(const wchar_t* fileName) : FileResource(fileName) { }

Texture2D::~Texture2D() {
	pResource = nullptr;
	pResourceView = nullptr;
	pSampler = nullptr;
}

void Texture2D::Create(ID3D11Device* device) {

	HRESULT hr;

	//read the texture file by file name
	//create the resource and resource view
	GFX_FAILED(dx::CreateWICTextureFromFile(device,this->fileName,&pResource,&pResourceView));

	//sampler description
	D3D11_SAMPLER_DESC pSd = {};
	pSd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	pSd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	pSd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	pSd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	pSd.ComparisonFunc = D3D11_COMPARISON_LESS;
	pSd.MinLOD = 0;
	pSd.MaxLOD = 0;

	GFX_FAILED(device->CreateSamplerState(&pSd, &pSampler));

}

wrl::ComPtr<ID3D11Resource> Texture2D::getResource() {
	return pResource;
}

wrl::ComPtr<ID3D11ShaderResourceView> Texture2D::getResouceView() {
	return pResourceView;
}

wrl::ComPtr<ID3D11SamplerState> Texture2D::getSampler() {
	return pSampler;
}

