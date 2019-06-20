#pragma once
#include "Graphics.h"
#include "UpdateController.h"

//this class represents an object that can be bound to the graphics pipeline
class Bindable {
public:

	~Bindable();
	Bindable();
	Bindable(Graphics gfx);
	
	//bind will setup the specified bindable object bind it to the graphics pipeline
	virtual void Bind() = 0;

	//update updates any changed resources, depending on the update controller state
	virtual void Update() = 0;
	
	static void setUpdateController(UpdateController controller);
	
	//updates the transform matrix per object
	static void UpdateTransformMatrix(dx::XMMATRIX m_transform);

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
	static wrl::ComPtr<ID3D11Buffer> m_Transform;


	//flags wether PS, VS, GFX object and m_Transform are already set
	static bool PSset, VSset,mTransformSet, GFXSet;

private:	

	//graphics object
	static Graphics gfx;

};

