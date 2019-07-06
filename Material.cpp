#include "Material.h"

Material::Material() {
	bind = ShaderBind::PS;
	RegisterID = 1;
	c = {1,1,1};
	r = {1,0.5f,4};
}

Material::~Material() { }

ComponentStruct* Material::getComponentStruct() {
	SMaterial m = {};
	m.Color = {c.r,c.g,c.b};
	m.Reflection = { r.d,r.s,r.n };
	return &m;
}

UINT Material::bufferSize() {
	return sizeof(SMaterial);
}

UINT Material::byteStride() {
	return sizeof(float);
}

int Material::RegID() {
	return RegisterID;
}

ShaderBind Material::shaderBind() {
	return bind;
}

void Material::setColor(float r, float g, float b) {
	if (r < 0) r = c.r;
	if (g < 0) g = c.g;
	if (b < 0) b = c.b;
	c = {r,g,b};
}

void Material::setReflection(float d, float s, float n) {
	if (d < 0) d = r.d;
	if (s < 0) s = r.s;
	if (n < 0) n = r.n;
	r = {d,s,n};
}
