#pragma once
#include "Graphics.h"
#include "FileReader.h"
//some macros for process file
#define END_OF_BLOCK "/"
#define VERTEX 348
#define FACE 102
#define VS 233
#define PS 227
#define TX 236
#define MATERIAL 109
#define COMMENT 35

//this class represents a mesh file that has been read externally
class MeshFile : public FileReader {
public:

	//calls process file to parse the file
	MeshFile(const wchar_t* fileName);
	~MeshFile();

	//returns geometric data read from the mesh file
	std::vector<int> getIndices();
	std::vector<Vertex> getVertices();

	//retrieves the read VS,PS and TX file names
	const wchar_t* getVSfileName();
	const wchar_t* getPSfileName();
	const wchar_t* getTXfileName();

	//material properties of the file *NOT YET*
	//SMaterial getMaterialProperties();

private:

	//Geometry vectors
	std::vector<int> indices;
	std::vector<Vertex> vertices;

	//proccesses the file into geoemtry (and material) data
	void ProcessFile();

	//stores the assigned VS,PS and TX
	const wchar_t* VSfileName;
	const wchar_t* PSfileName;
	const wchar_t* TXfileName;

	//tesselate a (convex!!) object into triangles
	//returns a vector of vectors, each vector being a triangle by itself
	std::vector<int> tesselate(std::vector<int> indices);

	//material
	//SMaterial material;

	//simple sum function
	int val(std::string s);

};

