#include "Bindable.h"

Bindable::~Bindable() {}


Bindable::Bindable(Graphics gfx){
	if (GFXSet) return;
	this->gfx = gfx;
}

void Bindable::setUpdateController(UpdateController controller) {
	UC = controller;
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
wrl::ComPtr<ID3D11Buffer> Bindable::m_Transform;

UpdateController Bindable::UC;