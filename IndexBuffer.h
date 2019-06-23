#pragma once
#include "Bindable.h"

//this class represents the bindable index buffer
class IndexBuffer : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;
	using Bindable::Unbind;

public:

	//takes a set of indices and stores them
	IndexBuffer(std::vector<int> Ind);
	~IndexBuffer();

	//binds the index buffer to the pipeline
	void Bind() override;
	//updated the index buffer and rebinds it
	void Update() override;
	//unbind and delete the object
	void Unbind() override;

private:

	//pointer to the buffer
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	//set of all indices
	std::vector<int> indices;

};

