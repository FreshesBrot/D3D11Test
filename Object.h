#pragma once
#include "Graphics.h"
#include "Component.h"
#include "Transform.h"
#include "Material.h"

//this class represents a general object and its possible operations
class Object {
public:

	//constructor for object
	Object();
	~Object();

	//returns the indices and vertices of the object
	virtual std::vector<int> getIndices() = 0;
	virtual std::vector<Vertex> getVertices() = 0;

	//retrieves and sets reource IDs of the object
	virtual int getVSID() = 0;
	void setVSID(int ID);
	virtual int getPSID() = 0;
	void setPSID(int ID);
	virtual int getTXID() = 0;
	void setTXID(int ID);

	//retrieves the specific shader file Name
	virtual const wchar_t* getVSfileName() = 0;
	virtual const wchar_t* getPSfileName() = 0;
	virtual const wchar_t* getTXfileName() = 0;

	//sets the filenames
	void setVSfile(const wchar_t* fileName);
	void setPSfile(const wchar_t* fileName);
	void setTXfile(const wchar_t* fileName);


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

	//world projection matrix
	static dx::XMMATRIX m_projection;

#pragma endregion



protected:

	//this vector stores the components the object has
	std::vector<Component*> components;

	//the file attributes of the object
	const wchar_t* VSfileName;
	const wchar_t* PSfileName;
	const wchar_t* TXfileName;
	
	//the Resource IDs of the object
	int PSID;
	int VSID;
	int TXID;
};
