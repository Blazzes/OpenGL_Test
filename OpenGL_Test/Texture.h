#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "ShaderLoad.h"

class Texture
{
public:
	Texture(const char* path, GLenum texType, GLint texRepeat, GLint texSmooth);
	GLuint getTexture();
	GLenum getTextureType();
	void textureBind(int activeTexture = GL_TEXTURE0);
	void textureUniform(ShaderLoad* shader, const char* pathShader);
private:
	GLuint texture = 0;
	GLenum type = GL_TEXTURE_2D;
	int bindTex = GL_TEXTURE0;
};

