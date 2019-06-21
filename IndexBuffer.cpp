#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(std::vector<int> Indcs) {
	indices = Indcs;
}

IndexBuffer::~IndexBuffer() {
	pIndexBuffer = nullptr;
}

void IndexBuffer::Bind() {

	HRESULT hr;

	D3D11_SUBRESOURCE_DATA pData = {};
	pData.pSysMem = indices.data();

	D3D11_BUFFER_DESC pBd = {};
	D3D11_BUFFER_DESC bd2 = {};
	bd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd2.Usage = D3D11_USAGE_DEFAULT;
	bd2.CPUAccessFlags = 0u;
	bd2.MiscFlags = 0u;
	bd2.ByteWidth = indices.size() * sizeof(int);
	bd2.StructureByteStride = sizeof(int);

	GFX_FAILED(getDevice()->CreateBuffer(&pBd, &pData, &pIndexBuffer));
	getContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);

}

void IndexBuffer::Update() {
	indices = UC.getNewIndices();
	Bind();
}
