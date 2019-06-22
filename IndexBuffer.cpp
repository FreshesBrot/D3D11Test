#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(std::vector<int> Indcs) {
	indices = Indcs;
}

IndexBuffer::~IndexBuffer() { }

void IndexBuffer::Bind() {

	HRESULT hr;

	//check if anything is in the vector; cannot allocate 0-size for buffer
	if (indices.empty()) {
		std::vector<int> i({ 0 });
		indices = i;
	}

	D3D11_SUBRESOURCE_DATA pData = {};
	pData.pSysMem = indices.data();
	pData.SysMemPitch = 0u;
	pData.SysMemSlicePitch = 0u;

	D3D11_BUFFER_DESC pBd = {};
	pBd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	pBd.Usage = D3D11_USAGE_DEFAULT;
	pBd.CPUAccessFlags = 0u;
	pBd.MiscFlags = 0u;
	pBd.ByteWidth = indices.size() * sizeof(int);
	pBd.StructureByteStride = sizeof(int);

	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	GFX_FAILED(getDevice()->CreateBuffer(&pBd, &pData, &pIndexBuffer));
	getContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);

}

void IndexBuffer::Update() {
	if (!UC.hasChanged(ID)) return;

	UC.setState(ID, false);
	
	indices = UC.getNewIndices();
	Bind();
}
