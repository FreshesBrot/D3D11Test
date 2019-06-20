#pragma once
#include "Bindable.h"

class VertexShader : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;

public:


	VertexShader(const wchar_t* fileName);
	~VertexShader();

	void Bind() override;
	void Update() override;

private:
	const wchar_t* fileName;
};

