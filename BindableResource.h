#pragma once
#include "Component.h"

//this class represents a bindable that takes a resource
class BindableResource {
public:
	
	//binds the specified resource
	virtual void BindResource(Component* comp) = 0;
	//creates the buffer from the specified resource
	virtual void CreateFromResource(Component* comp) = 0;
	//updates the resource
	virtual void UpdateFromResource(Component* comp) = 0;

};

