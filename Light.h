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

	//light specific functions
	
	//set the iight direction
	void setLightDirection(float x, float y, float z);

	//set the light color
	void setLightColor(float r, float g, float b);

	//set light ambient color
	void setAmbientColor(float r, float g, float b);

	//structs that hold light properties
	struct Direction {
		float x, y, z;
	};

	struct Color {
		float r, g, b;
	};

	struct Ambient {
		float r, g, b;
	};

private:
	
	//light properties
	Direction dir;
	float intensity;
	Color c;
	Ambient a;
};


