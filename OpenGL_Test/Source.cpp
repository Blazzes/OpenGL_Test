#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>
#include "ShaderLoad.h"
#include "Camera.h"
#include "MapObject.h"
#include "Window.h"
#include "Texture.h"

#define W 1000
#define H 1000

float coef = 0.5;

Camera* cam;

void scroll_callback(GLFWwindow* win, double x, double y)
{
	cam->mouseScrollEvent(y);
}

static GLfloat lastX = 400, lastY = 300;
void mouse_callback(GLFWwindow* win, double x, double y)
{
	cam->mouseMovmentEvent(x - lastX, lastY - y);
	lastX = x;
	lastY = y;
}

bool keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void do_moved()
{
	if (keys[GLFW_KEY_W])
		cam->keyboardEvent(Camera_Movement::FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		cam->keyboardEvent(Camera_Movement::BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		cam->keyboardEvent(Camera_Movement::LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		cam->keyboardEvent(Camera_Movement::RIGHT, deltaTime);
}

MapObject* myinit()
{

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	return new MapObject(vertices, sizeof(vertices));
}

void update(ShaderLoad* shader, MapObject* obj, Texture* tex)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Use();

	tex->textureBind();
	tex->textureUniform(shader, "ourTexture1");

	glm::mat4 view = cam->getViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(cam->getCameraData().zoom), (float)W / (float)H, 0.1f, 1000.0f);

	GLint modelLoc = glGetUniformLocation(shader->getProgram(), "model");
	GLint viewLoc = glGetUniformLocation(shader->getProgram(), "view");
	GLint projLoc = glGetUniformLocation(shader->getProgram(), "proj");
	
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(obj->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}

int main(int argv, char** argc)
{
	
	WIN->initWindow("TEST", W, H);

	glfwSetKeyCallback(WIN->getWindowPointer(), key_callback);
	glfwSetCursorPosCallback(WIN->getWindowPointer(), mouse_callback);
	glfwSetScrollCallback(WIN->getWindowPointer(), scroll_callback);
	glfwSetInputMode(WIN->getWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	cam = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	MapObject* obj =  myinit();

	ShaderLoad* shader = new ShaderLoad("./vertexShader.vert", "./fragmentShader.frag");

	Texture* tex = new Texture("awesomeface.jpg", GL_TEXTURE_2D, GL_REPEAT, GL_LINEAR);

	while (!glfwWindowShouldClose(WIN->getWindowPointer()))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		do_moved();
		update(shader, obj, tex);
		glfwSwapBuffers(WIN->getWindowPointer());
	}

	glfwTerminate();
	return 0;
}