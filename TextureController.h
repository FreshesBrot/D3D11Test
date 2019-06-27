#pragma once
#include "Bindable.h"
#include "Texture2D.h"
#include <unordered_map>


//this class wraps all needed textures and binds them
class TextureController : public Bindable {
public:

	//standard con- / destructor
	TextureController();
	~TextureController();

	//adds a texture to the collection and returns the ID of the texture for lookup
	//returns the texture id, if the texture is already contained
	int addTextureFile(const wchar_t* fileName);


	//bindable interface
	void Bind() override;
	void Update() override;
	void Unbind() override;


private:

	//this map stores all texture file names and associates them with a texture ID
	std::unordered_map<const wchar_t*, int> fileNames;
	//this map stores the pointers to the texture bindable
	std::unordered_map<int, Texture2D*> textures;

	//amount of textures
	int amtTextures = 0;

	//current texture state
	int textureState;
};

