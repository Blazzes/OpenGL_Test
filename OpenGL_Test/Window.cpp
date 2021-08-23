#include "Window.h"
#include <iostream>
Window* Window::instance()
{
    static Window* win= new Window("test", 100, 100);
    return win;
}

#ifdef TYPE_ONE
    Window* Window::instance(const char* title, GLuint windowWidth, GLuint windowHeight)
    {
        static Window* win = new Window(title, windowWidth, windowHeight);
        return win;
    }    
#endif

Window::Window(const char* title, GLuint windowWidth, GLuint windowHeight) : winW(windowWidth), winH(windowHeight)
{
#ifdef TYPE_ONE
    initWindow(title, windowWidth, windowHeight);
#endif // !TYPE_ONE
}

GLFWwindow* Window::getWindowPointer()
{
    return window;
}

GLint Window::initWindow(const char* title, GLuint windowWidth, GLuint windowHeigth)
{
    winW = windowWidth;
    winH = windowHeigth;
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeigth, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return -3;
    }

    glViewport(0, 0, winW, winH);
    glEnable(GL_DEPTH_TEST);
    std::cout << "window init" << std::endl;
    return 0;
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
