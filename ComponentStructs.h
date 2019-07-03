#pragma once
#include "Graphics.h"

//superclass for component structs
struct ComponentStruct {};

//these structs represent what properties component carries, and what is bound to the pipeline
struct STransform : ComponentStruct {
	//world transform matrix
	dx::XMMATRIX m_world;
};

struct SMaterial : ComponentStruct {
	//base color
	struct {
		float r, g, b;
	} Color;
	struct {
		float d, s, n;
	} Reflection;
};

struct SLight : ComponentStruct {

};