#include "UpdateController.h"

UpdateController::UpdateController() : m_Transform(),newVertices(),newIndices() { }

UpdateController::~UpdateController() { }

void UpdateController::set(dx::XMMATRIX transform) {
	m_Transform = transform;
}

void UpdateController::set(std::vector<Vertex> vertices) {
	newVertices = vertices;
}

void UpdateController::set(std::vector<int> indices) {
	newIndices = indices;
}

void UpdateController::setShaderState(int state) {
	shaderState = state;
}

dx::XMMATRIX UpdateController::getTransform() {
	return m_Transform;
}

std::vector<Vertex> UpdateController::getNewVertices() {
	return newVertices;
}

std::vector<int> UpdateController::getNewIndices() {
	return newIndices;
}

int UpdateController::getShaderState() {
	return shaderState;
}

