#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(std::vector<Vertex> Vrt) {
	vertices = Vrt;
}

VertexBuffer::~VertexBuffer() {
	pVertexBuffer = nullptr;
}

void VertexBuffer::Bind() {
	HRESULT hr;

	//check if vertices are empty; if so, return function
	if (vertices.empty()) return;

	const std::vector<Vertex> constVertex(vertices);

	//create subresource data
	D3D11_SUBRESOURCE_DATA pData = {};
	pData.pSysMem = constVertex.data();
	pData.SysMemPitch = 0u;
	pData.SysMemSlicePitch = 0u;

	//create buffer description
	CD3D11_BUFFER_DESC pBd = {};
	pBd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	pBd.Usage = D3D11_USAGE_DEFAULT;
	pBd.CPUAccessFlags = 0u;
	pBd.MiscFlags = 0u;
	pBd.ByteWidth = constVertex.size() * sizeof(Vertex);
	pBd.StructureByteStride = sizeof(Vertex);

	//create and bind buffer
	GFX_FAILED(getDevice()->CreateBuffer(&pBd, &pData, &pVertexBuffer));
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	getContext()->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	//set primitve type
	getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void VertexBuffer::Update() {
	vertices = UC->getNewVertices();
	Bind();
}

void VertexBuffer::Unbind() {
	this->~VertexBuffer();
}
