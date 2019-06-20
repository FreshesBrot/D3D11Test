#pragma once
#include "Graphics.h"
#include "UpdateController.h"

class Bindable {
public:

	~Bindable();
	Bindable(Graphics gfx);
	
	//bind will setup the specified bindable object bind it to the graphics pipeline
	virtual void Bind() = 0;
	//unbinds the component from the pipeline
	virtual void Unbind() = 0;

	//update updates any changed resources, depending on the update controller state
	virtual void Update() = 0;
	
	static void setUpdateController(UpdateController controller);

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


	//flags wether PS, VS and m_Transform are already set
	bool PSset = false, VSset = false,mTransformSet = false, GFXSet = false;

private:	

	//graphics object
	static Graphics gfx;

};

