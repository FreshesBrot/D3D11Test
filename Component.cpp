#include "Component.h"

dx::XMMATRIX Component::m_view;
dx::XMMATRIX Component::m_projection = dx::XMMatrixPerspectiveFovLH(1.0f, 1.0f, 0.5f, 100.0f);

void Component::UpdateView(dx::XMMATRIX viewMatrix) {
	m_view = viewMatrix;
}
