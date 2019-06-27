#pragma once
#include "Graphics.h"



//object transform descpriptions
struct Position {
	float x, y, z;
};

struct Rotation {
	float x, y, z;
};

struct Scale {
	float x, y, z;
};

//this class represents a general object and its possible operations
class Object {
public:

	//constructor for object
	Object();
	~Object();

	//returns the indices and vertices of the object
	virtual std::vector<int> getIndices() = 0;
	virtual std::vector<Vertex> getVertices() = 0;

	//returns the model transformation matrix for the object (non-projected)
	virtual dx::XMMATRIX getTransformMatrix() = 0;

	//retrieves and sets reource IDs of the object
	virtual int getShaderID() = 0;
	void setShaderID(int ID);
	virtual int getTextureID() = 0;
	void setTextureID(int ID);

	//retrieves the specific shader file Name
	virtual const wchar_t* getVSfileName() = 0;
	virtual const wchar_t* getPSfileName() = 0;
	virtual const wchar_t* getTXTfileName() = 0;

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

	//returns a struct with the objects position data
	Position getPosition();
	Rotation getRotation();
	Scale getScale();

	//world projection matrix
	static dx::XMMATRIX m_projection;

#pragma endregion



protected:

	//the objects transform data
	Position position;
	Rotation rotation;
	Scale scaling;

	//shortcuts
	dx::XMMATRIX trans(float xOffset, float yOffset, float zOffset);

	dx::XMMATRIX rotateXYZ(float xAngle, float yAngle, float zAngle);
	 
	dx::XMMATRIX scal(float xScale, float yScale, float zScale);

	//the file attributes of the object
	const wchar_t* VSfileName;
	const wchar_t* PSfileName;
	const wchar_t* TXTfileName;
	
	//the Resource IDs of the object
	int shaderID;
	int textureID;

};
