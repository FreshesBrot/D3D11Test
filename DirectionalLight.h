#pragma once
#include "Object.h"

//this struct carries the light information
struct Light {
	dx::XMFLOAT4 direction;
	dx::XMFLOAT4 ambient;
	dx::XMFLOAT4 diffuse;
};

//this class represents a directional light
class DirectionalLight : public Object {
public:

	
	Light getLight();

private: 

	//light properties
	dx::XMFLOAT4 direction;
	dx::XMFLOAT4 ambient;
	dx::XMFLOAT4 diffuse;

};

