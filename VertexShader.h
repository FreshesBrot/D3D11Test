#pragma once
#include "Bindable.h"

//this class represents the bindable vertexshader
class VertexShader : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;

public:


	VertexShader(const wchar_t* fileName);
	~VertexShader();

	//binds the vertex shader to the pipeline
	void Bind() override;
	//changes the set vertex shader
	void Update() override;

	//id of the bindable
	const static UINT ID = 1;

private:
	const wchar_t* fileName;
};

