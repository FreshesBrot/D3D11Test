#pragma once
#include "Graphics.h"

//this class represents a single pixel shader
class PixelShader {
public:

	//sets the filename of the shader
	PixelShader(const wchar_t* fileName);
	~PixelShader();

	//creates the shader object and stores the pointer
	void Create(ID3D11Device* device);

	//returns the pointer to the shader object
	ID3D11PixelShader* Get();

private:
	
	//file name of the shader
	const wchar_t* fileName;

	//the pointer to the shader object
	wrl::ComPtr<ID3D11PixelShader> pShader;
};

