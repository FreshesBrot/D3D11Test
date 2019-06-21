#pragma once
#include <vector>
#include <queue>

//this class represents the keyboard and its functionality
class Keyboard {
public:

	Keyboard();
	~Keyboard();

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

	//key states
	enum State {
		LOOSE, HOLD, RELEASE
	};

	//key event
	struct Event {
		State state;
		char keyCode;
		Event(State state, char c) {
			this->state = state;
			keyCode = c;
		}
	};

	//represents the state of the keyboard
	std::vector<State> states;
	std::queue<Event>  queue;

};

