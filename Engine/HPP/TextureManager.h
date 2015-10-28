
#pragma once

#include <map>
#include <string>

/*
TextureManager is a class for handling the loading of textures from file into memory and passing them on to the GPU.
Call the GetTexture function with a file name and it will load it into memory (if it hasn't been loaded already), and return
an integer identifier for the associated texture object in graphics memory.  You can use this id to enable the texture.
*/

class TextureManager
{
public:
	TextureManager(void);
	~TextureManager(void);

	// Loads a texture into memory and returns the id of the texture object created.
	int GetTexture(std::string fileName);

private:
	std::map<int, std::string> textures;
};

