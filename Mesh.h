#pragma once
#include "Object.h"
#include "MeshFile.h"

//this class represents a mesh object
class Mesh : public Object {
public:

	//construct a mesh from a mesh file
	Mesh(MeshFile mf);
	~Mesh();

	std::vector<int> getIndices() override;
	std::vector<Vertex> getVertices() override;

	int getVSID() override;
	int getPSID() override;
	int getTXID() override;

	const wchar_t* getVSfileName() override;
	const wchar_t* getPSfileName() override;
	const wchar_t* getTXfileName() override;

private:

	//the objects geometry data
	std::vector<int> indices;
	std::vector<Vertex> vertices;

};

