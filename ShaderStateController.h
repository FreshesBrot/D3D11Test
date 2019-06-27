#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "Bindable.h"
#include <sstream>
#include <string>
#include <unordered_map>

//this class encapsulates all shader files and controls which are bound to the pipeline
class ShaderStateController : public Bindable{
	using Bindable::Bind;
	using Bindable::Update;
	using Bindable::Unbind;
public:

	//standard con- / destructor
	ShaderStateController();
	//deletes all that is stored in the maps
	~ShaderStateController();
	
	//inserts a new shader; first looks, if the shader was already added to the map; if so, it wont add the shader
	//also returns the key where the shader will be or is already stored 
	int addShaderFile(const wchar_t* VSfileName, const wchar_t* PSfileName);

	//binds the shader defined by the shader state
	void Bind() override;

	//updates the bound shader defined by the shader state
	void Update() override;

	//undbinds the bindable
	void Unbind() override;

	//important for shader classes - delegate the getDevice(Context) calls from the bindable interface
	static ID3D11Device* getDevice();
	
private:
	
	//this map stores all string values
	std::unordered_map<const wchar_t*,int> shaderFileNames;
	//maps that store shader objects based on pointers
	std::unordered_map<int, VertexShader*> vertexShaders;
	std::unordered_map<int, PixelShader*> pixelShaders;

	//looks up wether a value is already in the map or not
	//bool contains(const wchar_t*);
	//bool contains(int i);

	//this int controls what shader is bound to the pipeline; updated via updatecontroller
	int shaderState;

	//this is the amount of shaders currently collected
	int amtShaders = 0;

};

