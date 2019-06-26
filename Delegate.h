#pragma once
#include "Graphics.h"

class GraphicsDelegate {
public:
	//delegates the getContext calls
	static ID3D11Device* getDevice() {
	};
	static ID3D11Context* getContext();

};