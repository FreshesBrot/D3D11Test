#pragma once
#include "Bindable.h"

class VertexShader : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;

public:

	~VertexShader();

	void Bind() override;
	void Update() override;

private:

};

