#pragma once
#include "FileResource.h"

//this class represents a single pixel shader
class PixelShader : public FileResource {
public:

	//sets the filename of the shader
	PixelShader(const wchar_t* fileName);
	~PixelShader();

	//creates the shader object and stores the pointer
	void Create(ID3D11Device* device) override;

	//returns the pointer to the shader object
	ID3D11PixelShader* Get();

private:

	//the pointer to the shader object
	wrl::ComPtr<ID3D11PixelShader> pShader;
};

