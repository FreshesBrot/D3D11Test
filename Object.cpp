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

#pragma region TRANSFORMS

void Object::setVSfile(const wchar_t* fileName) {
	VSfileName = fileName;
}

void Object::setPSfile(const wchar_t* fileName) {
	PSfileName = fileName;
}

void Object::setTXfile(const wchar_t* fileName) {
	TXfileName = fileName;
}

void Object::translate(float xOffset, float yOffset, float zOffset){
	static_cast<Transform*>(components[0])->translate(xOffset, yOffset, zOffset);
}

void Object::setTransform(float xPos, float yPos, float zPos) {
	static_cast<Transform*>(components[0])->setTransform(xPos, yPos, zPos);
}

void Object::rotate(float xAngle, float yAngle, float zAngle) {
	static_cast<Transform*>(components[0])->rotate(xAngle, yAngle, zAngle);
}

void Object::setRotation(float xAngle, float yAngle, float zAngle) {
	static_cast<Transform*>(components[0])->setRotation(xAngle, yAngle, zAngle);
}

void Object::scale(float xScaling, float yScaling, float zScaling) {
	static_cast<Transform*>(components[0])->scale(xScaling, yScaling, zScaling);
}

void Object::setScale(float xScale, float yScale, float zScale) {
	static_cast<Transform*>(components[0])->setScale(xScale, yScale, zScale);
}

#pragma endregion

void Object::setVSID(int ID)  {
	VSID = ID;
}

void Object::setPSID(int ID) {
	PSID = ID;
}

void Object::setTXID(int ID) {
	TXID = ID;
}
