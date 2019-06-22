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

	//updates the vertex buffer
	void Update() override;

	//id of the bindable
	const static UINT ID = 3;

private:

	std::vector<Vertex> vertices;

};

