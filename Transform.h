#pragma once
#include "Component.h"

struct Position {
	float x, y, z;
};

struct Rotation {
	float x, y, z;
};

struct Scale {
	float x, y, z;
};

//this class represents the transform of an object
class Transform : public Component {
public:

	Transform();
	~Transform();

	//returns the world transform matrix
	ComponentStruct* getComponentStruct() override;

	//returns buffer information
	UINT bufferSize() override;
	UINT byteStride() override;

	//returns register ID
	int RegID() override;

	//returns the ShaderBind
	ShaderBind shaderBind() override;

//transformation operations
#pragma region TRANSFORMATIONS
	//applies a continuous transformation
	void translate(float xOffset, float yOffset, float zOffset);

	//sets the coordinates of the object
	void setTransform(float xPos, float yPos, float zPos);

	//applies a continuous rotation around the X/Y/Z axis
	void rotate(float xAngle, float yAngle, float zAngle);

	//sets the rotation of the object
	void setRotation(float xAngle, float yAngle, float zAngle);

	//applies a continuous scaling to the object
	void scale(float xScaling, float yScaling, float zScaling);

	//sets the scale of the object
	void setScale(float xScale, float yScale, float zScale);

#pragma endregion

private:

	//positional data of the object
	Position position;
	Rotation rotation;
	Scale scaling;

	//shortcuts
	dx::XMMATRIX trans(float xOffset, float yOffset, float zOffset);

	dx::XMMATRIX rotateXYZ(float xAngle, float yAngle, float zAngle);

	dx::XMMATRIX scal(float xScale, float yScale, float zScale);

};

