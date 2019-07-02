#include "Bindable.h"


void Bindable::setGraphicsObject(Graphics* gfx) {
	Bindable::gfx = gfx;
}

void Bindable::setUpdateController(UpdateController* UC) {
	Bindable::UC = UC;
}

void Bindable::setWorldProjection(dx::XMMATRIX projection) {
	m_projection = projection;
}

ID3D11Device* Bindable::getDevice() {
	return gfx->device.Get();
}

ID3D11DeviceContext* Bindable::getContext() {
	return gfx->context.Get();
}



Graphics* Bindable::gfx;
UpdateController* Bindable::UC;
dx::XMMATRIX Bindable::m_projection;