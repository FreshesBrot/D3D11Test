#pragma once

//this class represents a vertex 
struct Vertex {
	struct {
		float x, y, z;
	} Pos;
	struct {
		float r, g, b;
	} Color;
	/*struct {
		float x,y,z;
	} normal;
	*/
	struct {
		float u,v;
	} texCoord;
	
};
