#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIN Window::instance()

#ifdef TYPE_ONE
	#define WIN(title, W, H) Window::instance(title, W, H)
	class Window
	{
	public:
		static Window* instance();
		static Window* instance(const char* title, GLuint windowWidth, GLuint windowHeight);
		GLFWwindow* getWindowPointer();
		~Window();
	private:
		Window(const char* title, GLuint windowWidth, GLuint windowHeight);
		GLuint winW, winH;
		GLFWwindow* window;
	};
#else
	class Window
	{
	public:
		static Window* instance();
		GLFWwindow* getWindowPointer();
	#ifndef TYPE_ONE
		GLint initWindow(const char* title, GLuint windowWidth, GLuint windowHeigth);
	#endif
		~Window();
	private:
	#ifdef TYPE_ONE
		GLint initWindow(const char* title, GLuint windowWidth, GLuint windowHeigth);
	#endif
		Window(const char* title, GLuint windowWidth, GLuint windowHeigth);
		GLuint winW, winH;
		GLFWwindow* window = nullptr;
	};
#endif