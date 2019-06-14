#pragma once
#include "Redef.h"
#include <queue>
#include <vector>

class Mouse {
public:

	Mouse();
	~Mouse();

	enum Button {
		L=0,R=1,W=2
	};

	enum State {
		LOOSE,HOLD,DBL,RELEASE,SCROLLUP,SCROLLDOWN
	};

	struct Event {
		Button button;
		State state;
		Event(Button b, State s) {
			button = b;
			state = s;
		};
	};

	//updates mouse position
	void UpdatePosition(POINTS p);
	//updates mouse state
	void Update();

	//return wether a button is down or not
	bool OnButtonDown(Button button);
	//same for double click
	bool OnDblClick(Button button);
	//return if mouse is scrolling (up or down)
	bool OnScrollUp();
	bool OnScrollDown();


	//control the mouse states
	void ButtonDown(Button button);
	void ButtonRelease(Button button);
	void ButtonDblClk(Button button);
	void MouseScroll(int amt);
	

	int xPos();
	int yPos();

private:

	std::vector<State> states;
	std::queue<Event> queue;

	int wheelDelta = 0;

	//mouse position coordinates
	int x = 0,y = 0;

};

