#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

class ShaderLoad
{
public:
	ShaderLoad(const char* vertexShader, const char* fragmentShader);
	void Use();
	GLuint getProgram();
private:
	GLuint program = 0;
};

