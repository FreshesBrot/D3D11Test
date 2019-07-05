#pragma once
#include "Component.h"

//specification of material attributes
struct Color {
	float r, g, b;
};

struct Reflection {
	float d, s, n;
};

//this class defines material properties of an object
class Material : public Component {
public:

	Material();
	~Material();

	//returns the material specifications
	ComponentStruct* getComponentStruct() override;

	//returns the buffer specifications
	UINT bufferSize() override;
	UINT byteStride() override;

	//returns the register ID
	int RegID() override;

	//returns ShaderBind
	ShaderBind shaderBind() override;

	//change material properties
	//input -1 to not change an attribute
	void setColor(float r, float g, float b);
	void setReflection(float d, float s, float n);

private:

	//material properties
	Color c;
	Reflection r;


};
