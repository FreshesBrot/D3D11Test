#include "Mouse.h"


Mouse::Mouse() {
	states.resize(3);
}

Mouse::~Mouse() {}

void Mouse::UpdatePosition(POINTS p) {
	x = p.x;
	y = p.y;

}

void Mouse::Update() {
	if (!queue.empty()) {
		Event e = queue.front();
		queue.pop();
		states[e.button] = e.state;
	}
}

bool Mouse::OnButtonDown(Button button) {
	return states[button] == HOLD;
}

bool Mouse::OnDblClick(Button button) {
	return states[button] == DBL;
}

bool Mouse::OnScrollUp() {
	return states[2] == SCROLLUP;
}

bool Mouse::OnScrollDown() {
	return states[2] == SCROLLDOWN;
}

void Mouse::ButtonDown(Button button) {
	if (states[button] != HOLD)
		queue.push({ button,HOLD });
}

void Mouse::ButtonRelease(Button button) {
	queue.push({ button,RELEASE});
	queue.push({ button,LOOSE });
}

void Mouse::ButtonDblClk(Button button) {
	queue.push({ button,DBL });
}

void Mouse::MouseScroll(int amt) {
	wheelDelta += amt;
	if (wheelDelta >= 120) {
		wheelDelta %= 120;
		queue.push({ W,SCROLLUP });
	}
	if (wheelDelta <= -120) {
		wheelDelta += 120;
		queue.push({ W,SCROLLDOWN });
	}
	queue.push({ W,LOOSE });
}

int Mouse::xPos() {
	return x;
}

int Mouse::yPos() {
	return y;
}




