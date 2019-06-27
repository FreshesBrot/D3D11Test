#include "TextureController.h"

TextureController::TextureController() { }

TextureController::~TextureController() {
	fileNames.clear();
	textures.clear();
}

int 
TextureController::addTextureFile(const wchar_t* fileName) {
	//if file name is a nullptr, return -1
	if (fileName == nullptr) return -1;

	//check if file was already added once
	std::unordered_map<const wchar_t*, int>::const_iterator it = fileNames.find(fileName);
	if (it == fileNames.end()) {
		//insert new pair
		fileNames.insert(std::make_pair(fileName, amtTextures++));
		int i = fileNames[fileName];

		Texture2D* tx = new Texture2D(fileName);
		tx->Create(getDevice());
		textures[i] = tx;
		return i;
	}
	return fileNames[fileName];

}


void TextureController::Bind() {
	//if there are no textures, return the function

	//if state is -1, the object has no ID -> cannot bind texture
	if (textureState == -1) return;
	
	//retrieve texture object
	Texture2D* tx = textures[textureState];
	
	//bind texture object
	getContext()->PSSetSamplers(0u, 1u, tx->getSampler().GetAddressOf());
	getContext()->PSSetShaderResources(0u, 1u, tx->getResouceView().GetAddressOf());

}

void TextureController::Update() {
	textureState = UC->getTextureState();
	Bind();
}

void TextureController::Unbind() {
	this->~TextureController();
}
