#pragma once
#include "Bindable.h"

//this class represents the bindable vertexbuffer
class VertexBuffer : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;

public:

	VertexBuffer(std::vector<Vertex> Vcs);
	~VertexBuffer();

	//binds the vertex buffer to the pipeline
	void Bind() override;

	void Update() override;


private:

	std::vector<Vertex> vertices;
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;

};

