#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(std::vector<Vertex> Vcs) {
	vertices = Vcs;
}

VertexBuffer::~VertexBuffer() { }

void VertexBuffer::Bind() {
	HRESULT hr;

	//check if anything is in the vector; cannot allocate 0-size for buffer
	if (vertices.empty()) {
		std::vector<Vertex> v({ {-1.0f,-1.0f,-1.0f,0.0f,0.0f,0.0f} });
		vertices = v;
	}

	D3D11_SUBRESOURCE_DATA pData = {};
	pData.pSysMem = vertices.data();
	pData.SysMemPitch = 0u;
	pData.SysMemSlicePitch = 0u;

	CD3D11_BUFFER_DESC pBd = {};
	pBd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	pBd.Usage = D3D11_USAGE_DEFAULT;
	pBd.CPUAccessFlags = 0u;
	pBd.MiscFlags = 0u;
	pBd.ByteWidth = vertices.size() * sizeof(Vertex);
	pBd.StructureByteStride = sizeof(Vertex);

	//create and set the vertex buffer
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	GFX_FAILED(getDevice()->CreateBuffer(&pBd,&pData,&pVertexBuffer));
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;

	getContext()->IASetVertexBuffers(0u,1u,pVertexBuffer.GetAddressOf(),&stride,&offset);

	//set the input layout
	wrl::ComPtr<ID3D11InputLayout> pInLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	GFX_FAILED(getDevice()->CreateInputLayout(ied, 2u, pVshaderBlob->GetBufferPointer(), pVshaderBlob->GetBufferSize(), &pInLayout));
	getContext()->IASetInputLayout(pInLayout.Get());

}

void VertexBuffer::Update() {
	if (!UC.hasChanged(ID)) return;
	
	UC.setState(ID, false);
	
	vertices = UC.getNewVertices();
	Bind();
}
