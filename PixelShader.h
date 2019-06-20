#pragma once
#include "Bindable.h"

class PixelShader : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;

public:

	PixelShader(const wchar_t* fileName);
	~PixelShader();

	void Bind() override;
	void Update() override;

private:
	const wchar_t* fileName;
};

