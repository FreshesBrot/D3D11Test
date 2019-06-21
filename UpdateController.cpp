#include "UpdateController.h"

UpdateController::UpdateController() : m_transform(),newVertices(),newIndices() { }

UpdateController::~UpdateController() { }

void UpdateController::set(dx::XMMATRIX transform) {
	m_transform = transform;
}

void UpdateController::set(std::vector<Vertex> vertices) {
	newVertices = vertices;
}

void UpdateController::set(std::vector<int> indices) {
	newIndices = indices;
}

dx::XMMATRIX UpdateController::getTransform() {
	return m_transform;
}

std::vector<Vertex> UpdateController::getNewVertices() {
	return newVertices;
}

std::vector<int> UpdateController::getNewIndices() {
	return newIndices;
}
