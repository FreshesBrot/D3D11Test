#pragma once
#include "Graphics.h"

//superclass for component structs
struct ComponentStruct {};

//these structs represent what properties a component carries, and what is bound to the pipeline

//struct that carries transform properties
struct STransform : ComponentStruct {
	//world, view and projection matrices
	dx::XMMATRIX m_world;	
	dx::XMMATRIX m_view;
	dx::XMMATRIX m_projection;
};

//struct that carries material properties
struct SMaterial : ComponentStruct {
	//base color
	struct {
		float r, g, b;
	} Color;
	//padding
	float pad1 = 0;
	//reflection properties
	struct {
		float d, s;
		int n;
	} Reflection;
	float pad2 = 0;
};

//struct that carries light properties
struct SLight : ComponentStruct {
	struct {
		dx::XMFLOAT3 dir;
	} Direction;
	float intensity;
	struct {
		dx::XMFLOAT3 color;
	} Color;
	float pad1 = 0;
	struct {
		dx::XMFLOAT3 diffuse;
	} Ambient;
	float pad2 = 0;
};
