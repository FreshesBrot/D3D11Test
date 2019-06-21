#pragma once
#include "Redef.h"
#include <queue>
#include <vector>

//shortcut macros
#define MouseL Mouse::Button::L
#define MouseR Mouse::Button::R
#define MouseM Mouse::Button::M


//this class represents the mouse and its functionality
class Mouse {
public:

	enum Button {
		L = 0,R = 1,M = 2
	};

	Mouse();

	//update the mouse position
	void UpdatePosition(POINTS p);
	
	//check state of the mouse
	bool OnButtonDown(Button button);
	bool OnButtonRelease(Button button);
	bool OnButtonLoose(Button button);
	bool OnScrollUp();
	bool OnScrollDown();

	//update mouse states
	void ButtonDown(Button button);
	void ButtonRelease(Button button);
	void Scroll(int value);

	void Update();

	//return x / y position of mouse
	int xPos();
	int yPos();

private:

	//state of the mouse
	enum State {
		HOLD,RELEASE,LOOSE,SCROLLUP,SCROLLDOWN
	};

	//mouse event
	struct Event {
		Button button;
		State state;
		Event(Button b, State t) {
			button = b;
			state = t;
		};
	};

	std::queue<Event> queue;
	std::vector<State> states;

	//mouse position coordinates
	int x,y;
	//wheel Delta state
	int wheelDelta;

};


