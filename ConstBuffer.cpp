#include "ConstBuffer.h"

#pragma region MATRIXBUFFER

MatrixBuffer::MatrixBuffer() {

}

MatrixBuffer::~MatrixBuffer() { 
	pConstBuffer = nullptr;
}

void MatrixBuffer::Bind() {
	HRESULT hr;
	
	//the struct that holds the information to be bound
	struct ConstBuffer {
		dx::XMMATRIX m_transform;
	} cb;
	cb = { dx::XMMATRIX() };

	//create buffer description
	CD3D11_BUFFER_DESC pBd = {};
	pBd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pBd.Usage = D3D11_USAGE_DYNAMIC;
	pBd.ByteWidth = sizeof(dx::XMMATRIX);
	pBd.StructureByteStride = 0u;
	pBd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pBd.MiscFlags = 0u;

	//create subresource
	D3D11_SUBRESOURCE_DATA pData = {};
	pData.pSysMem = &cb;
	pData.SysMemPitch = 0U;
	pData.SysMemSlicePitch = 0u;

	//create and bind constant buffer
	GFX_FAILED(getDevice()->CreateBuffer(&pBd, &pData, &pConstBuffer));
	getContext()->VSSetConstantBuffers(0u,1u,pConstBuffer.GetAddressOf());

}

void MatrixBuffer::Update() {
	HRESULT hr;

	dx::XMMATRIX transformationMatrix = UC->getTransform();
	
	D3D11_MAPPED_SUBRESOURCE pMsr;
	//fills the address with zeros
	ZeroMemory(&pMsr, sizeof(D3D11_MAPPED_SUBRESOURCE));
	//locks the resource and denies GPU access
	GFX_FAILED(getContext()->Map(pConstBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0, &pMsr));
	//update the matrix buffer
	struct ConstBuffer {
		dx::XMMATRIX m_transform;
	} cb;
	cb = { transformationMatrix };
	memcpy(pMsr.pData, &cb, sizeof(ConstBuffer));
	//unlock the resource
	getContext()->Unmap(pConstBuffer.Get(),0u);
}

void MatrixBuffer::Unbind() {
	this->~MatrixBuffer();
}

#pragma endregion

ConstBuffer::ConstBuffer() { }

ConstBuffer::~ConstBuffer() { }

void ConstBuffer::Bind() { }

void ConstBuffer::Update() { }

void ConstBuffer::Unbind() {
	this->~ConstBuffer();
}
