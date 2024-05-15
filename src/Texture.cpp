#include"Texture.h"
#include "stb/stb_image.h"
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum
	pixelType)
{
	type = texType;
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
	if (!bytes) std::cout << "Texture not found: " << image;
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);
	/*Współrzędne tekstury zazwyczaj mieszczą się w zakresie od (0,0) do (1,1), ale
	co się stanie, jeśli podamy współrzędne poza ten zakres? Domyślne
	zachowanie OpenGL polega na powtarzaniu obrazów tekstury (w zasadzie ignorujemy
	część całkowitą zmiennoprzecinkowych współrzędnych tekstury), ale
	istnieje więcej opcji oferowanych przez OpenGL:*/
	/*GL_REPEAT: Domyślne zachowanie dla tekstur. Powtarza obraz tekstury.
	GL_MIRRORED_REPEAT: To samo co GL_REPEAT, ale odbija obraz przy każdym
	powtórzeniu.
	GL_CLAMP_TO_EDGE: Ogranicza współrzędne między 0 a 1. Skutkiem tego jest to, że
	wyższe współrzędne są ograniczane do krawędzi.
	GL_CLAMP_TO_BORDER: Współrzędne poza zakresem otrzymują teraz określony przez
	użytkownika kolor obramowania.*/
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	/*Filtrowanie tekstur może być ustawione dla operacji powiększania i
	pomniejszania (przy zmianie skali w górę lub w dół), dzięki czemu na przykład
	można użyć filtrowania sąsiadów najbliższych, gdy tekstury są zmniejszane, oraz
	filtrowania liniowego dla tekstur powiększonych. Dlatego też musimy
	określić metodę filtrowania dla obu opcji za pomocą glTexParameter*/
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Dodatkowe linie dla GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType,
		bytes);
	// Mipmapy
	/*GL_NEAREST_MIPMAP_NEAREST: wybiera najbliższy poziom mipmapy pasujący do
	rozmiaru piksela i używa interpolacji najbliższych sąsiadów do próbkowania tekstury.
	GL_LINEAR_MIPMAP_NEAREST: wybiera najbliższy poziom mipmapy i próbkuje ten
	poziom za pomocą interpolacji liniowej.
	GL_NEAREST_MIPMAP_LINEAR: interpoluje liniowo między dwoma mipmapami, które
	najbardziej odpowiadają rozmiarowi piksela, i próbkuje
	poziom interpolowany za pomocą interpolacji najbliższych sąsiadów.
	GL_LINEAR_MIPMAP_LINEAR: interpoluje liniowo między dwoma najbliższymi mipmapami
	i próbkuje poziom interpolowany za pomocą interpolacji liniowej.*/
	glGenerateMipmap(texType);
	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}
void Texture::Bind()
{
	glBindTexture(type, ID);
}
void Texture::Unbind()
{
	glBindTexture(type, 0);
}
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}