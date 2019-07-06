#include "Object.h"

dx::XMMATRIX Object::m_projection = dx::XMMatrixPerspectiveFovLH(1.0f,1.0f,0.5f,100.0f);

Object::Object() {

	//push required materials
	components.push_back(new Transform());
	components.push_back(new Material());
}

Object::~Object() {
	for (Component* cmp : components)
		delete cmp;
}

void Object::setVSfile(const wchar_t* fileName) {
	VSfileName = fileName;
}

void Object::setPSfile(const wchar_t* fileName) {
	PSfileName = fileName;
}

void Object::setTXfile(const wchar_t* fileName) {
	TXfileName = fileName;
}

std::vector<Component*> Object::getComponents() {
	return components;
}

void Object::addComponent(Component* comp) {
	components.push_back(comp);
}

void Object::setVSID(int ID)  {
	VSID = ID;
}

void Object::setPSID(int ID) {
	PSID = ID;
}

void Object::setTXID(int ID) {
	TXID = ID;
}
