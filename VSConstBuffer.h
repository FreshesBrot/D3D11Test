#pragma once
#include "ConstBuffer.h"

//this class represents a const buffer that is bound to the vertex shader
class VSConstBuffer : public ConstBuffer {
public:

	VSConstBuffer();
	~VSConstBuffer();

	void Bind() override;
	void Update() override;
	void Unbind() override;

	
	void BindResource(Component* comp) override;
	void CreateFromResource(Component* comp) override;
	void UpdateFromResource(Component* comp) override;
};

