#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MapObject
{
public:
	MapObject(const char* objectPath);
	MapObject(GLfloat* vertices, size_t verticesSize, GLuint* indices = 0, size_t indicesSize = 0);
	~MapObject();
	GLuint getVBO();
	GLuint getVAO();
	GLuint getEBO();
private:
	GLuint VBO, VAO, EBO;
};

