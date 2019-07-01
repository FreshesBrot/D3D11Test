#pragma once
#include "Graphics.h"
#include "WICTextureLoader.h"
#include "FileResource.h"

//this class represents a 2D texture that can be bound to the pipeline
class Texture2D : public FileResource {
public:

	//standard con- / destructor; 
	//takes the filename and stores it
	Texture2D(const wchar_t* fileName);
	~Texture2D();

	//creates the resources
	void Create(ID3D11Device* device) override;

	//retrieves the pointers 
	wrl::ComPtr<ID3D11Resource> getResource();
	wrl::ComPtr<ID3D11ShaderResourceView> getResouceView();
	wrl::ComPtr<ID3D11SamplerState> getSampler();

private:

	//resource, view and sampler pointer
	wrl::ComPtr<ID3D11Resource> pResource = nullptr;
	wrl::ComPtr<ID3D11ShaderResourceView> pResourceView = nullptr;
	wrl::ComPtr<ID3D11SamplerState> pSampler = nullptr;

};

