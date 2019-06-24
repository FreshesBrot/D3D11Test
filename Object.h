#pragma once
#include "Graphics.h"


//this class represents a general object and its possible operations
class Object {
public:

	//constructor for object
	Object();
	~Object();

	//returns the indices and vertices of the object
	virtual std::vector<int> getIndices() = 0;
	virtual std::vector<Vertex> getVertices() = 0;

	//returns the transformationmatrix for the object (already projected into NDC)
	virtual dx::XMMATRIX getTransformMatrix() = 0;

#pragma region TRANSFORMS
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

protected:

	//world projection matrix; shared for all objects
	static dx::XMMATRIX m_projection;

	//the objects transform data
	struct {
		float x, y, z;
	} position;

	struct {
		float x, y, z;
	} scaling;

	struct {
		float x, y, z;
	} rotation;

	//shortcuts
	dx::XMMATRIX trans(float xOffset, float yOffset, float zOffset);

	dx::XMMATRIX rotateX(float angle);
	dx::XMMATRIX rotateY(float angle);
	dx::XMMATRIX rotateZ(float angle);

	dx::XMMATRIX scal(float xScale, float yScale, float zScale);


};
