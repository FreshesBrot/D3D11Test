#pragma once
#include "Graphics.h"
#include "UpdateController.h"

//this class represents the general functionality of all objects that are bound to the graphics pipeline
class Bindable {
public:

	//undbinds and deletes the object
	virtual void Unbind() = 0;

	//bind the component to the pipeline
	virtual void Bind() = 0;

	//update the bound component
	virtual void Update() = 0;

	//sets the graphics object
	static void setGraphicsObject(Graphics* gfx);

	//sets the update controller
	static void setUpdateController(UpdateController* UC);

	//updates the shader blob
	static void updateShaderBlob(ID3DBlob* pBlob);

protected:
	//retrieves the pointer to the D3D device
	static ID3D11Device* getDevice();

	//retrieves the pointer to the D3D device context
	static ID3D11DeviceContext* getContext();

	//shader blob (for the vertexbuffer)
	static wrl::ComPtr<ID3DBlob> pShaderBlob;

	//shared update controller
	static UpdateController* UC;

private:
	//the shared graphics object
	static Graphics* gfx;

};

