#include "Light.h"

Light::Light() {
	bind = ShaderBind::PS;
	RegisterID = 0;
	dir = {0,0,1};
	intensity = 0.8f;
	c = {1,1,1};
	a = {0.2f,0.2f,0.2f};
}

Light::~Light() { }

int Light::RegID() {
	return RegisterID;
}

ComponentStruct* Light::getComponentStruct() {
	SLight l = {};
	l.Direction = { dx::XMFLOAT3(-dir.x,-dir.y,-dir.z) };
	l.intensity = intensity;
	l.Color = { dx::XMFLOAT3(c.r,c.g,c.b) };
	l.Ambient = { dx::XMFLOAT3(a.r,a.g,a.b) };
	return &l;
}

UINT Light::bufferSize() {
	return sizeof(SLight);
}

UINT Light::byteStride() {
	return sizeof(float);
}

ShaderBind Light::shaderBind() {
	return bind;
}

void Light::setLightDirection(float x, float y, float z) {
	dir = {x,y,z};
}

void Light::setLightColor(float r, float g, float b) {
	c = { r,g,b };
}

void Light::setAmbientColor(float r, float g, float b) {
	a = { r,g,b };
}
