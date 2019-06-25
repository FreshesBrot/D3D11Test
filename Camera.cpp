#include "Camera.h"

Camera::Camera() {
	position = {0,0,5};
}

std::vector<int> Camera::getIndices() {
	return std::vector<int>();
}

std::vector<Vertex> Camera::getVertices() {
	return std::vector<Vertex>();
}

dx::XMMATRIX Camera::getTransformMatrix() {
	dx::XMVECTOR v_position = { position.x,position.y,position.z};
	dx::XMVECTOR v_at = { 0,0,0 };
	dx::XMVECTOR v_up = { 0,1,0 };
	
	return dx::XMMatrixLookAtRH(v_position, v_at, v_up);

}
