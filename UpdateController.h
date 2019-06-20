#pragma once
#include <vector>

//this class serves as a change-state observer between the graphics interface and the bindable interface
class UpdateController {
public:
	UpdateController();
	~UpdateController();

	bool hasChanged(int i);
	void setState(bool state, int i);

private:
	//harbors in each slot wether the bindable changed
	//0: PShader - 1: VShader - 2: VertBuffer - 3: IndBuffer - 4: ConstBuffer
	std::vector<bool> state;
};

