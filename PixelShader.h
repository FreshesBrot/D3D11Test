#pragma once
#include "Bindable.h"

//this class represents the bindable pixelshader
class PixelShader : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;

public:

	PixelShader(const wchar_t* fileName);
	~PixelShader();

	//binds the pixel shader to the pipeline
	void Bind() override;
	//updates the set shader
	void Update() override;
	
	//id of the bindable
	const static UINT ID = 0;

private:
	const wchar_t* fileName;
};

