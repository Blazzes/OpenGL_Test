#include "Texture.h"
#include <iostream>
Texture::Texture(const char* path, GLenum texType, GLint texRepeat, GLint texSmooth) : type(texType)
{
	glGenTextures(1, &texture);
	glBindTexture(texType, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texRepeat);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texRepeat);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texSmooth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texSmooth);

	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	glTexImage2D(texType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(texType);
	SOIL_free_image_data(image);
	glBindTexture(texType, 0);
	std::cout << "TEXTURE LOAD" << std::endl;
}

GLuint Texture::getTexture()
{
	return texture;
}

GLenum Texture::getTextureType()
{
	return type;
}

void Texture::textureBind(int activeTexture)
{
	bindTex = activeTexture;
	glActiveTexture(activeTexture);
	glBindTexture(type, texture);
}

void Texture::textureUniform(ShaderLoad* shader, const char* pathShader)
{
	shader->Use();
	glUniform1i(glGetUniformLocation(shader->getProgram(), pathShader), bindTex - GL_TEXTURE0);
}
