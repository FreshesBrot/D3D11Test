#include "ShaderStateController.h"

ShaderStateController::ShaderStateController() { }

ShaderStateController::~ShaderStateController() {
	VSFileNames.clear();
	PSFileNames.clear();
	textureFileNames.clear();
	vertexShaders.clear();
	pixelShaders.clear();
	textures.clear();
}

int ShaderStateController::addVSFile(const wchar_t* VSfileName) {
	if (VSfileName == nullptr) return -1;
	return add(VSfileName, new VertexShader(VSfileName));
}

int ShaderStateController::addPSFile(const wchar_t* PSfileName) {
	if (PSfileName == nullptr) return -1;
	return add(PSfileName,new PixelShader(PSfileName));
}

int ShaderStateController::addTextureFile(const wchar_t* textureFileName) {
	if (textureFileName == nullptr) return -1;
	return add(textureFileName, new Texture2D(textureFileName));
}

void ShaderStateController::Bind() {
	//call the bind functions
	bindVS();
	bindPS();
	bindTX();
}

void ShaderStateController::Update() {
	//update states
	VSState = UC->getVSState();
	PSState = UC->getPSState();
	textureState = UC->getTextureState();
	//bind again
	Bind();
}

void ShaderStateController::Unbind() {
	this->~ShaderStateController();
}

ID3D11Device* ShaderStateController::getDevice() {
	return Bindable::getDevice();
}

int ShaderStateController::add(const wchar_t* fileName, VertexShader* VS) {
	
	std::unordered_map<const wchar_t*, int>::const_iterator it = VSFileNames.find(fileName);
	if (it == VSFileNames.end()) {
		//insert new pair
		VSFileNames.insert(std::make_pair(fileName, amtVSShaders));
		//create resources
		VS->Create(getDevice());
		//store resource at location
		vertexShaders[amtVSShaders] = VS;
		//return location
		return amtVSShaders++;
	}
	//delete the file
	delete VS;
	//return location
	return VSFileNames[fileName];
}

int ShaderStateController::add(const wchar_t* fileName, PixelShader* PS) {
	std::unordered_map<const wchar_t*, int>::const_iterator it = PSFileNames.find(fileName);
	if (it == PSFileNames.end()) {
		PSFileNames.insert(std::make_pair(fileName, amtPSShaders));
		PS->Create(getDevice());
		pixelShaders[amtPSShaders] = PS;
		return amtPSShaders++;
	}
	delete PS;
	return PSFileNames[fileName];
}

int ShaderStateController::add(const wchar_t* fileName, Texture2D* T2D) {
	
	std::unordered_map<const wchar_t*, int>::const_iterator it = textureFileNames.find(fileName);
	if (it == textureFileNames.end()) {
		textureFileNames.insert(std::make_pair(fileName,amtTextures));
		T2D->Create(getDevice());
		textures[amtTextures] = T2D;
		return amtTextures++;
	}

	delete T2D;
	return textureFileNames[fileName];
}

void ShaderStateController::bindVS() {
	//check if state is valid
	if (VSState == -1) return;
	//check if state has changed
	if (VSState == tmpVS) return;
	//update temp state if the state did change
	tmpVS = VSState;

	//retrieve the resource object
	VertexShader* vs = vertexShaders[VSState];
	//bind it to the pipeline
	getContext()->VSSetShader(vs->Get(), nullptr, 0u);
	getContext()->IASetInputLayout(vs->GetIL());
}

void ShaderStateController::bindPS() {
	if (PSState == -1) return;
	if (PSState == tmpPS) return;
	
	tmpPS = PSState;

	PixelShader* ps = pixelShaders[PSState];
	getContext()->PSSetShader(ps->Get(), nullptr, 0u);
}

void ShaderStateController::bindTX() {
	if (textureState == -1) return;
	if (textureState == tmpTX) return;
	tmpTX = textureState;

	Texture2D* tx = textures[textureState];
	getContext()->PSSetSamplers(0u, 1u, tx->getSampler().GetAddressOf());
	getContext()->PSSetShaderResources(0u, 1u, tx->getResouceView().GetAddressOf());
}
