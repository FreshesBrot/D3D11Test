#pragma once
#include "Graphics.h"

//this class forwards the device and device context for the shaders
//no other use
class GraphicsDelegate {
public:

	static ID3D11Device* getDevice(Graphics* gfx) {
		return gfx->device.Get();
	};
	static ID3D11DeviceContext* getContext(Graphics* gfx) {
		return gfx->context.Get();
	};

};