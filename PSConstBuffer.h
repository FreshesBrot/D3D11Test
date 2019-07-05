#pragma once
#include "ConstBuffer.h"

//this class represents a constant buffer that is bound to the pixelshader
class PSConstBuffer : public ConstBuffer {
public:

	PSConstBuffer();
	~PSConstBuffer();

	//bindable interface
	void Bind() override;
	void Update() override;
	void Unbind() override;

	//bindable resource interface
	void BindResource(Component* comp) override;
	void CreateFromResource(Component* comp) override;
	void UpdateFromResource(Component* comp) override;

};

