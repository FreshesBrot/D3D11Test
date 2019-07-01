#pragma once
#include "FileResource.h"

//this class represents a single vertex shader
class VertexShader : public FileResource {
public:

	//sets the filename of the shader
	VertexShader(const wchar_t* fileName);
	~VertexShader();

	//creates the shader object and stores the pointer
	void Create(ID3D11Device* device) override;


	//returns the pointer to the shader object
	ID3D11VertexShader* Get();
	//returns the pointer to the input layout
	ID3D11InputLayout* GetIL();

private:

	//pointer to the shader object
	wrl::ComPtr<ID3D11VertexShader> pShader;
	//pointer to the specific input layout
	wrl::ComPtr<ID3D11InputLayout> pIL;

};

