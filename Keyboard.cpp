#include "Keyboard.h"

Keyboard::Keyboard() {
	
	queue.resize(256);
	
}

Keyboard::~Keyboard() {}

bool Keyboard::isPressed(char c) {
	return queue[(int)c] == HOLD;
}

bool Keyboard::OnRelease(char c) {
	return queue[(int)c] == RELEASE;
}

bool Keyboard::isLoose(char c) {
	return queue[(int)c] == LOOSE;
}

void Keyboard::Loose(char c) {
	queue[(int)c] = LOOSE;
}

void Keyboard::Press(char c) {
	queue[(int)c] = HOLD;
}

void Keyboard::Release(char c) {
	queue[(int)c] = RELEASE;
}