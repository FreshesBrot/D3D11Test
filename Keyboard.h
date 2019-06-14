#pragma once
#include <vector>
#include <queue>

class Keyboard {
public:

	Keyboard();
	~Keyboard();

	enum State {
		LOOSE,HOLD,RELEASE
	};

	struct Event {
		State state;
		char keyCode;
		Event(State state, char c) {
			this->state = state;
			keyCode = c;
		}
	};

	//keyboard interface to ask for keystates
	bool isPressed(char c);
	bool OnRelease(char c);
	bool isLoose(char c);

	//keyboard interface to update keystates
	void Press(char c);
	void Release(char c);

	//updates keyboard queue
	void Update();

private:

	std::vector<State> states;
	std::queue<Event>  queue;

};

