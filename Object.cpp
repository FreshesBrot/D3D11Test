#include "Object.h"

dx::XMMATRIX Object::m_projection = dx::XMMatrixPerspectiveLH(1.0f,1.0f,0.5f,20.0f);

Object::Object() {
	position = { 0,0,5 };
	rotation = { 0,0,0 };
	scaling = { 1,1,1 };
}

Object::~Object() { }

#pragma region TRANSFORMS

void Object::translate(float xOffset, float yOffset, float zOffset){
	position.x += xOffset;
	position.y += yOffset;
	position.z += zOffset;
}

void Object::setTransform(float xPos, float yPos, float zPos) {
	position.x = xPos;
	position.y = yPos;
	position.z = zPos;
}

void Object::rotate(float xAngle, float yAngle, float zAngle) {
	rotation.x += xAngle;
	rotation.y += yAngle;
	rotation.z += zAngle;
}

void Object::setRotation(float xAngle, float yAngle, float zAngle) {
	rotation.x = xAngle;
	rotation.y = yAngle;
	rotation.z = zAngle;
}

void Object::scale(float xScaling, float yScaling, float zScaling) {
	scaling.x += xScaling;
	scaling.y += yScaling;
	scaling.z += zScaling;
}

void Object::setScale(float xScale, float yScale, float zScale) {
	scaling.x = xScale;
	scaling.y = yScale;
	scaling.z = zScale;
}

Position Object::getPosition() {
	return position;
}
Rotation Object::getRotation() {
	return rotation;
}
Scale Object::getScale() {
	return scaling;
}
#pragma endregion

#pragma region SHORTCUTS
dx::XMMATRIX Object::trans(float xOffset, float yOffset, float zOffset) {
	return dx::XMMatrixTranslation(xOffset, yOffset, zOffset);
}

dx::XMMATRIX Object::rotateX(float angle) {
	return dx::XMMatrixRotationX(angle);
}

dx::XMMATRIX Object::rotateY(float angle) {
	return dx::XMMatrixRotationY(angle);
}

dx::XMMATRIX Object::rotateZ(float angle) {
	return dx::XMMatrixRotationZ(angle);
}

dx::XMMATRIX Object::scal(float xScale, float yScale, float zScale) {
	return dx::XMMatrixScaling(xScale, yScale, zScale);
}
#pragma endregion