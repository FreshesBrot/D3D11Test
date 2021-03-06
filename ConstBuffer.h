#pragma once
#include "Bindable.h"
#include "BindableResource.h"
#include "Component.h"

//this class represents a bindable constant buffer
class ConstBuffer : public Bindable, public BindableResource {
	using Bindable::Bind;
	using Bindable::Update;
	using Bindable::Unbind;
public:
	//for later implementation
	ConstBuffer();
	~ConstBuffer();

	void Bind() override;
	void Update() override;
	void Unbind() override;

protected:

	//pointer the the buffer resource
	wrl::ComPtr<ID3D11Buffer> pBuffer;
	//register ID ; bind slot for the buffer
	int bindSlot;

};

//this class represents the matrix buffer for the vertex shader
class MatrixBuffer : public ConstBuffer {
	using Bindable::Bind;
	using Bindable::Update;
	using Bindable::Unbind;
public:

	//standard con- / destructor
	MatrixBuffer();
	~MatrixBuffer();

	//binds the matrix buffer
	void Bind() override;
	//updates the matrix resource
	void Update() override;
	//unbinds and deletes the object
	void Unbind() override;

private:

	//pointer to the constant buffer
	wrl::ComPtr<ID3D11Buffer> pConstBuffer;

};
