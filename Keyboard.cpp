#include "Keyboard.h"

Keyboard::Keyboard() {
	//initialize state vector
	states.resize(256);
}

Keyboard::~Keyboard() {}


bool Keyboard::isPressed(char c) {
	return states[(int)c] == HOLD;
}

bool Keyboard::OnRelease(char c) {
	return states[(int)c] == RELEASE;
}

bool Keyboard::isLoose(char c) {
	return states[(int)c] == LOOSE;
}

//event queue functions

void Keyboard::Press(char c) {
	if (states[(int)c] != HOLD)
	queue.push({ HOLD,c });
}

void Keyboard::Release(char c) {
	queue.push({ RELEASE,c });
	queue.push({ LOOSE,c });
}

void Keyboard::Update() {
	if (queue.empty()) return;
	Event e = queue.front();
	queue.pop();
	states[(int)e.keyCode] = e.state;
}