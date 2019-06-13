#pragma once
#include <bitset>
#include <vector>

class Keyboard {
public:

	Keyboard();
	~Keyboard();

	enum State {
		LOOSE,HOLD,RELEASE
	};

	bool isPressed(char c);
	bool OnRelease(char c);
	bool isLoose(char c);

	void Press(char c);
	void Release(char c);
	void Loose(char c);

private:

	std::vector<State> queue;

};

