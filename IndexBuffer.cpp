#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(std::vector<int> Ind) {
	indices = Ind;
}

IndexBuffer::~IndexBuffer() { 
	pIndexBuffer = nullptr;
}

void IndexBuffer::Bind() {
	HRESULT hr;

	//check if indices are emtpy; if so, return function
	if (indices.empty()) return;

	const std::vector<int> constIndex(indices);

	//create subresource data
	D3D11_SUBRESOURCE_DATA pData = {};
	pData.pSysMem = constIndex.data();
	pData.SysMemPitch = 0u;
	pData.SysMemSlicePitch = 0u;

	//create buffer description
	CD3D11_BUFFER_DESC pBd = {};
	pBd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	pBd.Usage = D3D11_USAGE_DEFAULT;
	pBd.CPUAccessFlags = 0u;
	pBd.MiscFlags = 0u;
	pBd.ByteWidth = constIndex.size() * sizeof(int);
	pBd.StructureByteStride = sizeof(int);

	//create and bind buffer
	GFX_FAILED(getDevice()->CreateBuffer(&pBd,&pData,&pIndexBuffer));
	getContext()->IASetIndexBuffer(pIndexBuffer.Get(),DXGI_FORMAT_R32_UINT,0u);

}

void IndexBuffer::Update() {
	indices = UC->getNewIndices();
	Bind();
}

void IndexBuffer::Unbind() {
	this->~IndexBuffer();
}
