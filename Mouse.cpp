#include "Mouse.h"


void Mouse::UpdatePosition(POINTS p) {
	x = p.x;
	y = p.y;

}

int Mouse::xPos() {
	return x;
}

int Mouse::yPos() {
	return y;
}




