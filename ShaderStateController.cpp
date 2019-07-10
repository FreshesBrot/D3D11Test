#include "ShaderStateController.h"

ShaderStateController::ShaderStateController() {
}

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

void ShaderStateController::initializeDefaults() {
	const wchar_t* dfVS = L"defaultVS.cso";
	const wchar_t* dfPS = L"defaultPS.cso";
	const wchar_t* dfTX = L"defaultTX.jpg";

	//insert default elements at -1
	VSFileNames.insert(std::make_pair(dfVS, -1));
	VertexShader* vs = new VertexShader(dfVS);
	vs->Create(getDevice());
	vertexShaders[-1] = vs;

	PSFileNames.insert(std::make_pair(dfPS, -1));
	PixelShader* ps = new PixelShader(dfPS);
	ps->Create(getDevice());
	pixelShaders[-1] = ps;

	textureFileNames.insert(std::make_pair(dfTX, -1));
	Texture2D* tx = new Texture2D(dfTX);
	tx->Create(getDevice());
	textures[-1] = tx;
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

#pragma region FILEADDS
int ShaderStateController::add(const wchar_t* fileName, VertexShader* Vs) {

	std::unordered_map<const wchar_t*, int>::const_iterator it = VSFileNames.find(fileName);
	if (it == VSFileNames.end()) {
		//insert new pair
		VSFileNames.insert(std::make_pair(fileName, amtVSShaders));
		//create resources
		Vs->Create(getDevice());
		//store resource at location
		vertexShaders[amtVSShaders] = Vs;
		//return location
		return amtVSShaders++;
	}
	//delete the file
	delete Vs;
	//return location
	return VSFileNames[fileName];
}

int ShaderStateController::add(const wchar_t* fileName, PixelShader* Ps) {
	std::unordered_map<const wchar_t*, int>::const_iterator it = PSFileNames.find(fileName);
	if (it == PSFileNames.end()) {
		PSFileNames.insert(std::make_pair(fileName, amtPSShaders));
		Ps->Create(getDevice());
		pixelShaders[amtPSShaders] = Ps;
		return amtPSShaders++;
	}
	delete Ps;
	return PSFileNames[fileName];
}

int ShaderStateController::add(const wchar_t* fileName, Texture2D* Tx) {
	
	std::unordered_map<const wchar_t*, int>::const_iterator it = textureFileNames.find(fileName);
	if (it == textureFileNames.end()) {
		textureFileNames.insert(std::make_pair(fileName,amtTextures));
		Tx->Create(getDevice());
		textures[amtTextures] = Tx;
		return amtTextures++;
	}

	delete Tx;
	return textureFileNames[fileName];
}

#pragma endregion

void ShaderStateController::bindVS() {
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
	if (PSState == tmpPS) return;
	
	tmpPS = PSState;

	PixelShader* ps = pixelShaders[PSState];
	getContext()->PSSetShader(ps->Get(), nullptr, 0u);
}

void ShaderStateController::bindTX() {
	if (textureState == tmpTX) return;
	tmpTX = textureState;

	Texture2D* tx = textures[textureState];
	getContext()->PSSetSamplers(0u, 1u, tx->getSampler().GetAddressOf());
	getContext()->PSSetShaderResources(0u, 1u, tx->getResouceView().GetAddressOf());
}
