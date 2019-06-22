#include "ConstBuffer.h"

void ConstBuffer::Bind() {
}

void ConstBuffer::Update() {
}

#pragma region MATRIXBUFFER

MatrixBuffer::MatrixBuffer() : matrix() { }

MatrixBuffer::MatrixBuffer(dx::XMMATRIX matrix) {
	this->matrix = matrix;
}

MatrixBuffer::~MatrixBuffer() { 
	pTransform = nullptr; 
}

void MatrixBuffer::Bind() {
	if (mTransformSet) return;
	mTransformSet = true;

	HRESULT hr;

	const TransformMatrix cb = { matrix };

	CD3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(dx::XMMATRIX);
	cbd.StructureByteStride = 0u;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;

	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	csd.SysMemPitch = 0u;
	csd.SysMemSlicePitch = 0u;

	GFX_FAILED(getDevice()->CreateBuffer(&cbd, &csd, &pTransform));
	getContext()->VSSetConstantBuffers(0u, 1u, pTransform.GetAddressOf());

}

void MatrixBuffer::Update() {
	HRESULT hr;

	matrix = UC.getTransform();
	const TransformMatrix cb = { matrix };
	D3D11_MAPPED_SUBRESOURCE msr;
	//lock the transform buffer to overwrite it
	GFX_FAILED(getContext()->Map(pTransform.Get(),
		0u,D3D11_MAP_WRITE_DISCARD,0u,
		&msr));
	memcpy(msr.pData,&cb,sizeof(TransformMatrix));
	//unlock it
	getContext()->Unmap(pTransform.Get(),0u);
}

#pragma endregion


