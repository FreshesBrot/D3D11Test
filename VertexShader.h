#pragma once
#include "Bindable.h"

//this class represents the bindable vertex shader
class VertexShader : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;
	using Bindable::Unbind;

public:

	//takes the name of the shader file and stores it
	VertexShader(const wchar_t* fileName);
	~VertexShader();

	//binds the Vertex shader to the pipeline and stores the shader file blob for later use
	void Bind() override;
	//unused
	void Update() override;

	//undbind and delete the object
	void Unbind() override;

private:
	//file name of the shader
	const wchar_t* fileName;

};