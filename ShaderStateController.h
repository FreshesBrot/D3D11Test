#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture2D.h"
#include "Bindable.h"
#include <sstream>
#include <string>
#include <unordered_map>

//this class encapsulates all shader files and controls which are bound to the pipeline
class ShaderStateController : public Bindable {
	using Bindable::Bind;
	using Bindable::Update;
	using Bindable::Unbind;
public:

	//standard con- / destructor
	ShaderStateController();
	//deletes all that is stored in the maps
	~ShaderStateController();
	
	//inserts a new file resource; first looks, if the file resource was already added to the map; if so, it wont add the file
	//also returns the key where the file will be or is already stored 
	int addPSFile(const wchar_t* PSfileName);
	int addVSFile(const wchar_t* VSfileName);
	int addTextureFile(const wchar_t* textureFileName);

	//intiliazes default textures
	void initializeDefaults();

	//binds the shader defined by the shader state
	void Bind() override;

	//updates the bound shader defined by the shader state
	void Update() override;

	//undbinds the bindable
	void Unbind() override;

	//important for shader classes - delegate the getDevice(Context) calls from the bindable interface
	static ID3D11Device* getDevice();
	
private:
	
	//looks up if the file was already stored
	int add(const wchar_t* fileName,VertexShader* Vs);
	int add(const wchar_t* fileName, PixelShader* Ps);
	int add(const wchar_t* fileName, Texture2D* Tx);

	//bind the components according to the state
	void bindVS();
	void bindPS();
	void bindTX();

	//these maps stores all file names and their key
	std::unordered_map<const wchar_t*,int> VSFileNames;
	std::unordered_map<const wchar_t*, int> PSFileNames;
	std::unordered_map<const wchar_t*, int> textureFileNames;
	//maps that store file objects based on pointers
	std::unordered_map<int, VertexShader*> vertexShaders;
	std::unordered_map<int, PixelShader*> pixelShaders;
	std::unordered_map<int, Texture2D*> textures;

	//this int controls what shader is bound to the pipeline; updated via updatecontroller
	int PSState = -1;
	int VSState = -1;
	int textureState = -1;

	//these are for temporary storage of previous state values
	int tmpPS = -1;
	int tmpVS = -1;
	int tmpTX = -1;

	//this is the amount of specific files currently collected
	int amtPSShaders = 0;
	int amtVSShaders = 0;
	int amtTextures  = 0;

};

