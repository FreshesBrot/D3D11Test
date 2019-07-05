#include "PSConstBuffer.h"

PSConstBuffer::PSConstBuffer() { }

PSConstBuffer::~PSConstBuffer() {
	pBuffer = nullptr;
}

void PSConstBuffer::Bind() {
	getContext()->PSSetConstantBuffers(bindSlot, 1u, pBuffer.GetAddressOf());
}

void PSConstBuffer::Update() { }

void PSConstBuffer::Unbind() {
	this->~PSConstBuffer();
}

void PSConstBuffer::BindResource(Component* comp) {
	getContext()->PSSetConstantBuffers(comp->RegID(), 1u, pBuffer.GetAddressOf());
}

void PSConstBuffer::CreateFromResource(Component* comp) {
	HRESULT hr;
	
	bindSlot = comp->RegID();

	D3D11_SUBRESOURCE_DATA pData = {};
	pData.pSysMem = comp->getComponentStruct();
	pData.SysMemPitch = 0;
	pData.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC pBd = {};
	pBd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pBd.Usage = D3D11_USAGE_DYNAMIC;
	pBd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;;
	pBd.MiscFlags = 0;
	pBd.ByteWidth = comp->bufferSize();
	pBd.StructureByteStride = comp->byteStride();
	
	GFX_FAILED(getDevice()->CreateBuffer(&pBd,&pData,&pBuffer));
	getContext()->PSSetConstantBuffers(comp->RegID(), 1u, pBuffer.GetAddressOf());

}

void PSConstBuffer::UpdateFromResource(Component* comp) {
	HRESULT hr;

	D3D11_MAPPED_SUBRESOURCE pMsr;
	GFX_FAILED(getContext()->Map(pBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &pMsr));
	memcpy(pMsr.pData, comp->getComponentStruct(), comp->bufferSize());
	getContext()->Unmap(pBuffer.Get(),0u);
}
