#pragma once
#include "ComponentStructs.h"

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

protected:

	int RegisterID;

};

//this enum defines if a component is bound to the vertex or pixelshader
enum ShaderBind {
	VS = 0, PS = 1
};

