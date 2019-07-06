#pragma once
#include "Component.h"
#include "Components.h"

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

	//retrieves the vector of all components
	std::vector<Component*> getComponents();

	//retrieves the specified component
	template <class T> 
	T GetComponent() {
		for (Component* comp : components)
			if (dynamic_cast<const T>(comp) != nullptr) return static_cast<T>(comp);
		return nullptr;
	};

	//world projection matrix
	static dx::XMMATRIX m_projection;

	//add a component to the object
	void addComponent(Component* comp);

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
