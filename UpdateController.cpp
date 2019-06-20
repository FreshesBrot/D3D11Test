#include "UpdateController.h"

UpdateController::UpdateController() {
	state.resize(5);
}

UpdateController::~UpdateController() { }

bool UpdateController::hasChanged(int i) {
	return state[i];
}

void UpdateController::setState(bool state, int i) {
	this->state[i] = state;
}
