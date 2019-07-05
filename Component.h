#pragma once
#include "ComponentStructs.h"


//this enum defines if a component is bound to the vertex or pixelshader
enum ShaderBind {
	VS = 0, PS = 1
};

//this class represents a component that an object carries
class Component {
public:

	//retrieves the register ID that this component is bound to
	virtual int RegID() = 0;

	//retrieves the component struct
	virtual ComponentStruct* getComponentStruct() = 0;

	//relevant for binding the buffer; gives information about the required buffer size and bytestride
	virtual UINT bufferSize() = 0;
	virtual UINT byteStride() = 0;

	//returns the shader bind
	virtual ShaderBind shaderBind() = 0;

	//update the view matrix
	static void UpdateView(dx::XMMATRIX viewMatrix);


protected:

	//view and projection matrix
	static dx::XMMATRIX m_view;
	static dx::XMMATRIX m_projection;

	//the shader the component is bound to
	ShaderBind bind;

	//the register that the component is bound to
	int RegisterID;

};



