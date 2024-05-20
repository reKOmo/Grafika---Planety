#include"Texture.h"
#include "stb/stb_image.h"

TextureManager GlobalTextureManager;

Texture::Texture(const char* image, std::string texType)
{
	type = texType;
	int widthImg, heightImg, numColCh;
	//stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
	if (!bytes) std::cout << "Texture not found: " << image;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLenum format = GL_RED;
	if (numColCh == 3)
		format = GL_RGB;
	else if (numColCh == 4)
		format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

Texture TextureManager::loadTexture(std::string path, std::string texType, GLenum format, GLenum pixelType)
{
	std::cout << "Loading texture: " << path << "\n";
	if (loadedTexturesIndex.find(path) != loadedTexturesIndex.end()) {
		//key found
		return loadedTexturesIndex[path];
	}
	//load new texture
	return Texture(path.c_str(), texType);
}
