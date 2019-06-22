#pragma once
#include "Bindable.h"

//this class represents a  bindable constant buffer 
class ConstBuffer : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;
public:

	//binds the constant buffer to the pipeline
	void Bind() override;

	//updates the constant buffer that is bound
	void Update() override;

	//ID of the bindable
	const static UINT ID = 4;

private:	

};

//this class represents the buffer that holds matrix information
class MatrixBuffer : public ConstBuffer {
public:

	MatrixBuffer();
	MatrixBuffer(dx::XMMATRIX matrix);
	~MatrixBuffer();

	//binds the transform matrix to the buffer
	void Bind() override;
	//updates the transformation matrix
	void Update() override;

	//id of the bindable
	const static UINT ID = 5;

private:

	//the to-be-bound matrix
	dx::XMMATRIX matrix;

	//this struct holds the transform matrix that is bound to the pipeline
	struct TransformMatrix {
		dx::XMMATRIX m_transform;
	};

};