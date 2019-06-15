#pragma once
#include "Redef.h"
#include <vector>

class Mouse {
public:

	enum Button {
		L,R
	};

	enum State {
		LDOWN,LRELEASE,LLOOSE,RDOWN,RRELEASE,RLOOSE,SCROLLUP,SCROLLDOWN,
	};

	void UpdatePosition(POINTS p);
	bool IsDown(Button button);
	
	void ButtonDown(Button button);

	int xPos();
	int yPos();

private:



	//mouse position coordinates
	int x,y;

};

