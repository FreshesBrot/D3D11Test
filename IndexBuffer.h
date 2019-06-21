#pragma once
#include "Bindable.h"

//this class represents the bindable indexbuffer
class IndexBuffer : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;

public:

	IndexBuffer(std::vector<int> Indcs);
	~IndexBuffer();

	//binds the index buffer to the pipeline
	void Bind() override;

	//overwrites the indexbuffer
	void Update() override;



private:

	std::vector<int> indices;
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;

};

