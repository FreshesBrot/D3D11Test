#include "ShaderStateController.h"

ShaderStateController::ShaderStateController() : shaderState(-1){ }

ShaderStateController::~ShaderStateController() {
	shaderFileNames.clear();
	vertexShaders.clear();
	pixelShaders.clear();
}

int ShaderStateController::addShaderFile(const wchar_t* VSfileName, const wchar_t* PSfileName) {
	//if either file is a nullptr, return -1
	if (VSfileName == nullptr || PSfileName == nullptr) return -1;

	//check if the shader was added before (VS is the "main" shader file; PS depends on VS!)
	std::unordered_map<const wchar_t*,int>::const_iterator it = shaderFileNames.find(VSfileName);
	if (it == shaderFileNames.end()) {
		//get value of filename key
		shaderFileNames.insert(std::make_pair(VSfileName,amtShaders++));
		int i = shaderFileNames[VSfileName];

		//create shader object and store in order of creation
		VertexShader* vs = new VertexShader(VSfileName);
		vs->Create(getDevice());
		vertexShaders[i] = vs;
		PixelShader* ps = new PixelShader(PSfileName);
		ps->Create(getDevice());
		pixelShaders[i] = ps;

		return i;

	}

	//if it was, return the ID of the shader
	return shaderFileNames[VSfileName];

}

void ShaderStateController::Bind() {
	//if state is -1, either its a new initialization or the object has no valid ID
	if (shaderState == -1) return;

	//look up position in vector of shaders by ID

	PixelShader* PS = pixelShaders[shaderState];
	VertexShader* VS = vertexShaders[shaderState];

	//binds the retrieved shader objects
	getContext()->PSSetShader(PS->Get(), nullptr, 0u);
	getContext()->VSSetShader(VS->Get(), nullptr, 0u);
	getContext()->IASetInputLayout(VS->GetIL());
}

void ShaderStateController::Update() {
	shaderState = Bindable::UC->getShaderState();
	Bind();
}

void ShaderStateController::Unbind() {
	this->~ShaderStateController();
}

ID3D11Device* ShaderStateController::getDevice() {
	return Bindable::getDevice();
}