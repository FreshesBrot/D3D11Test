#pragma once
#include <vector>
#include <queue>

#pragma region KEYS
#define SHIFT 16
#define SPACE 32
#define BACKSPACE 8
#define CTRL 17
#define RETURN 13
#define NUM0 48
#define NUM1 49
#define NUM2 50
#define NUM3 51
#define NUM4 52
#define NUM5 53
#define NUM6 54 
#define NUM7 55
#define NUM8 56
#define NUM9 57
#pragma endregion

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

