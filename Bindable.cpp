#include "Bindable.h"


void Bindable::setGraphicsObject(Graphics* gfx) {
	Bindable::gfx = gfx;
}

void Bindable::setUpdateController(UpdateController* UC) {
	Bindable::UC = UC;
}

void Bindable::updateShaderBlob(ID3DBlob* pBlob) {
	pShaderBlob = nullptr;
	pShaderBlob = pBlob;
}

ID3D11Device* Bindable::getDevice() {
	return gfx->device.Get();
}

ID3D11DeviceContext* Bindable::getContext() {
	return gfx->context.Get();
}



Graphics* Bindable::gfx;
UpdateController* Bindable::UC;
wrl::ComPtr<ID3DBlob> Bindable::pShaderBlob;