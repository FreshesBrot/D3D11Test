#include "Camera.h"

Camera::Camera() {
	PSfileName = nullptr;
	VSfileName = nullptr;
	TXfileName = nullptr;
}

dx::XMMATRIX Camera::ViewTransform() {
	dx::XMVECTOR v_pos = dx::XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
	dx::XMVECTOR v_target = dx::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	dx::XMVECTOR v_up = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	return dx::XMMatrixLookAtLH(v_pos,v_target,v_up);
}

