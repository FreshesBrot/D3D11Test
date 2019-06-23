#pragma once
#include "Bindable.h"

//this class represents the bindable pixel shader
class PixelShader : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;
	using Bindable::Unbind;

public:

	//takes the name of the shader file and stores it
	PixelShader(const wchar_t* fileName);
	~PixelShader();

	//binds the pixel shader to the pipeline
	void Bind() override;
	//unused
	void Update();
	//unbinds and deletes the object
	void Unbind() override;

private:
	//file name of the shader
	const wchar_t* fileName;

};

