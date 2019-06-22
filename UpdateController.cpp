#include "UpdateController.h"

UpdateController::UpdateController() : m_Transform(),newVertices(),newIndices() {
	changes.resize(5);
}

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

dx::XMMATRIX UpdateController::getTransform() {
	return m_Transform;
}

std::vector<Vertex> UpdateController::getNewVertices() {
	return newVertices;
}

std::vector<int> UpdateController::getNewIndices() {
	return newIndices;
}

bool UpdateController::hasChanged(int i) {
	return changes[i];
}

void UpdateController::setState(int i, bool state) {
	changes[i] = state;
}
