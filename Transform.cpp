#include "Transform.h"

Transform::Transform() {
	bind = ShaderBind::VS;
	RegisterID = 0;
	position = { 0,0,5 };
	rotation = { 0,0,0 };
	scaling = { 1,1,1 };
}

Transform::~Transform() { }

ComponentStruct* Transform::getComponentStruct() {
	STransform t = {};
	t.m_projection = Component::m_projection;
	t.m_view = Component::m_view;
	t.m_world = (rotateXYZ(rotation.x, rotation.y, rotation.z) *
		scal(scaling.x, scaling.y, scaling.z) *
		trans(position.x, position.y, position.z));
	return &t;
}

UINT Transform::bufferSize() {
	return sizeof(STransform);
}

UINT Transform::byteStride() {
	return sizeof(dx::XMMATRIX);
}

int Transform::RegID() {
	return RegisterID;
}

ShaderBind Transform::shaderBind() {
	return bind;
}

#pragma region TRANSFORMATIONS
void Transform::translate(float xOffset, float yOffset, float zOffset) {
	position.x += xOffset * Time::deltaTime;
	position.y += yOffset * Time::deltaTime;
	position.z += zOffset * Time::deltaTime;
}

void Transform::setTransform(float xPos, float yPos, float zPos) {
	position.x = xPos;
	position.y = yPos;
	position.z = zPos;
}

void Transform::rotate(float xAngle, float yAngle, float zAngle) {
	rotation.x += xAngle * Time::deltaTime;
	rotation.y += yAngle * Time::deltaTime;
	rotation.z += zAngle * Time::deltaTime;
}

void Transform::setRotation(float xAngle, float yAngle, float zAngle) {
	rotation.x = xAngle;
	rotation.y = yAngle;
	rotation.z = zAngle;
}

void Transform::scale(float xScaling, float yScaling, float zScaling) {
	scaling.x += xScaling * Time::deltaTime;
	scaling.y += yScaling * Time::deltaTime;
	scaling.z += zScaling * Time::deltaTime;
}

void Transform::setScale(float xScale, float yScale, float zScale) {
	scaling.x = xScale;
	scaling.y = yScale;
	scaling.z = zScale;
}

dx::XMMATRIX Transform::trans(float xOffset, float yOffset, float zOffset) {
	return dx::XMMatrixTranslation(xOffset, yOffset, zOffset);
}

dx::XMMATRIX Transform::rotateXYZ(float xAngle, float yAngle, float zAngle) {
	return dx::XMMatrixRotationX(xAngle) * dx::XMMatrixRotationY(yAngle) * dx::XMMatrixRotationZ(zAngle);
}

dx::XMMATRIX Transform::scal(float xScale, float yScale, float zScale) {
	return dx::XMMatrixScaling(xScale, yScale, zScale);
}

#pragma endregion