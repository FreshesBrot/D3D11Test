#pragma once
#include "Graphics.h"

//superclass for component structs
struct ComponentStruct {};

//these structs represent what properties a component carries, and what is bound to the pipeline
struct STransform : ComponentStruct {
	//world view and projection matrices
	dx::XMMATRIX m_world;	
	dx::XMMATRIX m_view;
	dx::XMMATRIX m_projection;
};

struct SMaterial : ComponentStruct {
	//base color
	struct {
		float r, g, b;
	} Color;
	//reflection properties
	struct {
		float d, s, n;
	} Reflection;
};

struct SLight : ComponentStruct {

};
