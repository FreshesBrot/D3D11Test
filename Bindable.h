#pragma once
#include "Graphics.h"
#include "UpdateController.h"

//this class represents an object that can be bound to the graphics pipeline
class Bindable {
public:

	~Bindable();
	Bindable();
	
	//bind will setup the specified bindable object and bind it to the graphics pipeline
	virtual void Bind() = 0;

	//update updates any changed resources, depending on the update controller state
	virtual void Update() = 0;
	
	//sets the shared updatecontroller for the graphicsinterface and the bindable interface
	static void setUpdateController(UpdateController controller);
	
	//sets the graphics device
	static void setGraphicsDevice(Graphics graphics);

protected:

	//update controller
	static UpdateController UC;

	//returns device and device context
	static ID3D11Device* getDevice();
	static ID3D11DeviceContext* getContext();

	//static members for shared access
	static wrl::ComPtr<ID3D11PixelShader> pPshader;
	static wrl::ComPtr<ID3D11VertexShader> pVshader;
	static wrl::ComPtr<ID3DBlob> pVshaderBlob;
	static wrl::ComPtr<ID3D11Buffer> pTransform;


	//flags wether PS, VS, GFX object and m_Transform are already set
	static bool PSset, VSset,mTransformSet, GFXSet;

private:	

	//graphics object
	static Graphics gfx;

};

