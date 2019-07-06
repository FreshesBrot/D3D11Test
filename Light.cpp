#include "Light.h"

Light::Light() {
	bind = ShaderBind::PS;
	RegisterID = 0;
	dir = {0,0,-1};
	intensity = 1.0f;
	c = {1,1,1,1};
	a = {0.2f,0.2f,0.2f,1};
}

Light::~Light() { }

int Light::RegID() {
	return RegisterID;
}

ComponentStruct* Light::getComponentStruct() {
	SLight l = {};
	l.Direction = { dx::XMFLOAT3(dir.x,dir.y,dir.z) };
	l.intensity = intensity;
	l.Color = { dx::XMFLOAT4(c.r,c.g,c.b,c.a) };
	l.Ambient = { dx::XMFLOAT4(a.r,a.g,a.b,a.a) };
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
