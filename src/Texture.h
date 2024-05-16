#pragma once
#include<glad/glad.h>
#include <map>
#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	std::string type;
	Texture(const char* image, std::string texType);
	Texture() {
		ID = 0;
	}
	// Deletes a texture
	void Delete();
};

class TextureManager {
	std::map<std::string, Texture> loadedTexturesIndex;

public:
	TextureManager() {
		std::cout << "Init Texture Manager\n";
	}
	Texture loadTexture(std::string path, std::string texType, GLenum format, GLenum pixelType);
};

extern TextureManager GlobalTextureManager;