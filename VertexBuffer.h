#pragma once
#include "Bindable.h"

//this class represents the bindable vertex buffer
class VertexBuffer : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;
	using Bindable::Unbind;

public:

	//takes a set of vertices and stores them
	VertexBuffer(std::vector<Vertex> Vrt);
	~VertexBuffer();

	//binds the vertex buffer to the pipeline
	void Bind() override;
	//updated the vertex buffer and rebinds it
	void Update() override;

	//undbind and delete the object
	void Unbind() override;

private:
	
	//pointer to the buffer resource
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;

	//set of vertices
	std::vector<Vertex> vertices;

};

