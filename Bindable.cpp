#include "Bindable.h"

Bindable::Bindable() { }

Bindable::~Bindable() {}

void Bindable::setUpdateController(UpdateController controller) {
	UC = controller;
}

void Bindable::setGraphicsDevice(Graphics graphics) {
	if (GFXSet) return;
	GFXSet = true;
	gfx = graphics;
}

ID3D11Device* Bindable::getDevice() {
	return gfx.device.Get();
}

ID3D11DeviceContext* Bindable::getContext() {
	return gfx.context.Get();
}

//static declaration
Graphics Bindable::gfx;

wrl::ComPtr<ID3D11PixelShader> Bindable::pPshader;
wrl::ComPtr<ID3D11VertexShader> Bindable::pVshader;
wrl::ComPtr<ID3DBlob> Bindable::pVshaderBlob;
wrl::ComPtr<ID3D11Buffer> Bindable::pTransform;

UpdateController Bindable::UC;
bool Bindable::PSset = false, Bindable::VSset = false, Bindable::mTransformSet = false, Bindable::GFXSet = false;