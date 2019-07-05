#include "VSConstBuffer.h"

VSConstBuffer::VSConstBuffer() { }

VSConstBuffer::~VSConstBuffer() {
	pBuffer = nullptr;
}

void VSConstBuffer::Bind() {
	getContext()->VSGetConstantBuffers(bindSlot, 1u, pBuffer.GetAddressOf());
}

void VSConstBuffer::Update() { }

void VSConstBuffer::Unbind() { }

void VSConstBuffer::BindResource(Component* comp) {
	getContext()->VSSetConstantBuffers(comp->RegID(), 1u, pBuffer.GetAddressOf());
}

void VSConstBuffer::CreateFromResource(Component* comp) {
	HRESULT hr;
	
	//save the bind slot
	bindSlot = comp->RegID();

	//setup subresource
	D3D11_SUBRESOURCE_DATA pData;
	pData.pSysMem = comp->getComponentStruct();
	pData.SysMemPitch = 0;
	pData.SysMemSlicePitch = 0;

	//setup buffer description
	D3D11_BUFFER_DESC pBd = {};
	pBd.Usage = D3D11_USAGE_DYNAMIC;
	pBd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pBd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	pBd.MiscFlags = 0;
	pBd.ByteWidth = comp->bufferSize();
	pBd.StructureByteStride = comp->byteStride();

	//create buffer
	GFX_FAILED(getDevice()->CreateBuffer(&pBd,&pData,&pBuffer));

	//bind buffer
	getContext()->VSSetConstantBuffers(comp->RegID(), 1u, pBuffer.GetAddressOf());
}

void VSConstBuffer::UpdateFromResource(Component* comp) {
	HRESULT hr;

	D3D11_MAPPED_SUBRESOURCE pMsr = {};
	GFX_FAILED(getContext()->Map(pBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &pMsr));
	memcpy(pMsr.pData, comp->getComponentStruct(), comp->bufferSize());
	getContext()->Unmap(pBuffer.Get(), 0u);

}
