#include "Mesh.h"

Mesh::Mesh(MeshFile mf) : 
	indices(mf.getIndices()),
	vertices(mf.getVertices())
{
	VSfileName = mf.getVSfileName();
	PSfileName = mf.getPSfileName();
	TXfileName = mf.getTXfileName();
}

Mesh::~Mesh() { }

std::vector<int> Mesh::getIndices() {
	return indices;
}

std::vector<Vertex> Mesh::getVertices() {
	return vertices;
}

int Mesh::getVSID() {
	return VSID;
}

int Mesh::getPSID() {
	return PSID;
}

int Mesh::getTXID() {
	return TXID;
}

const wchar_t* Mesh::getVSfileName() {
	return VSfileName;
}

const wchar_t* Mesh::getPSfileName() {
	return PSfileName;
}

const wchar_t* Mesh::getTXfileName() {
	return TXfileName;
}
