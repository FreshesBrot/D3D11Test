#pragma once
#include "Component.h"

//this class represents a light component
class Light : public Component {
public:

	Light();
	~Light();

	//retrieve bind slot
	int RegID() override;

	//get component struct
	ComponentStruct* getComponentStruct() override;

	//buffer descriptions
	UINT bufferSize() override;
	UINT byteStride() override;

	//return the shader bind
	ShaderBind shaderBind() override;

	//structs that hold light properties
	struct Direction {
		float x, y, z;
	};
	struct Color {
		float r, g, b, a;
	};

	struct Ambient {
		float r, g, b, a;
	};

private:
	
	//light properties
	Direction dir;
	float intensity;
	Color c;
	Ambient a;
};


