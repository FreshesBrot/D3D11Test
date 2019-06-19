#include "Mouse.h"


Mouse::Mouse() : x(0),y(0),wheelDelta(0) {
	states.resize(3);
}

void Mouse::UpdatePosition(POINTS p) {
	x = p.x;
	y = p.y;

}

bool Mouse::OnButtonDown(Button button) {
	return states[button] == HOLD;
}

bool Mouse::OnButtonRelease(Button button) {
	return states[button] == RELEASE;
}

bool Mouse::OnButtonLoose(Button button) {
	return states[button] == LOOSE;
}

bool Mouse::OnScrollUp() {
	return states[M] == SCROLLUP;
}

bool Mouse::OnScrollDown() {
	return states[M] == SCROLLDOWN;
}

int Mouse::xPos() {
	return x;
}

int Mouse::yPos() {
	return y;
}

void Mouse::ButtonDown(Button button) {
	if(states[button] != HOLD)
	queue.push({button,HOLD});
}

void Mouse::ButtonRelease(Button button) {
	queue.push({ button,RELEASE });
	queue.push({button,LOOSE});
}

void Mouse::Scroll(int value) {
	wheelDelta += value;
	if (wheelDelta >= 120) {
		wheelDelta -= 120;
		queue.push({ M,SCROLLUP });
		queue.push({ M,LOOSE });
	}
	if (wheelDelta <= -120) {
		wheelDelta += 120;
		queue.push({ M,SCROLLDOWN });
		queue.push({ M,LOOSE });
	}

}

void Mouse::Update() {
	if (!queue.empty()) {
		Event e = queue.front();
		queue.pop();
		states[e.button] = e.state;
	}
	
}
