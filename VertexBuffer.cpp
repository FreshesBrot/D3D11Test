#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(std::vector<Vertex> Vcs) {
	vertices = Vcs;
}

VertexBuffer::~VertexBuffer() {
	pVertexBuffer = nullptr;
}

void VertexBuffer::Bind() {
	HRESULT hr;

	D3D11_SUBRESOURCE_DATA pData = {};
	pData.pSysMem = vertices.data();

	CD3D11_BUFFER_DESC pBd = {};
	pBd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	pBd.Usage = D3D11_USAGE_DEFAULT;
	pBd.CPUAccessFlags = 0u;
	pBd.MiscFlags = 0u;
	pBd.ByteWidth = vertices.size() * sizeof(Vertex);
	pBd.StructureByteStride = sizeof(Vertex);

	GFX_FAILED(getDevice()->CreateBuffer(&pBd,&pData,&pVertexBuffer));
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;

	getContext()->IASetVertexBuffers(0u,1u,pVertexBuffer.GetAddressOf(),&stride,&offset);

}

void VertexBuffer::Update() { }
