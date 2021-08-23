#include "MapObject.h"
#include <iostream>
MapObject::MapObject(const char* objectPath)
{
	
}

MapObject::MapObject(GLfloat* vertices, size_t verticesSize, GLuint* indices, size_t indicesSize)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	if (indices && indicesSize) glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
	if (indices && indicesSize)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);
}

MapObject::~MapObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

GLuint MapObject::getVBO()
{
	return VBO;
}

GLuint MapObject::getVAO()
{
	return VAO;
}

GLuint MapObject::getEBO()
{
	return EBO;
}
