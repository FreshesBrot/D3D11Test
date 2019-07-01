#include "Camera.h"

Camera::Camera() {
	position = {0,0,-0.5f};
	PSfileName = nullptr;
	VSfileName = nullptr;
	TXfileName = nullptr;
}


dx::XMMATRIX Camera::getTransformMatrix() {
	dx::XMVECTOR v_position = dx::XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
	dx::XMVECTOR v_at = dx::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	dx::XMVECTOR v_up = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	
	return dx::XMMatrixLookAtLH(v_position,v_at,v_up);

}
