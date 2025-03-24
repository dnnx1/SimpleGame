#include <assert.h>
#include "external/GLFW/glfw3.h"
#include "external/GL/glew.h"
#include "general/inc/window.h"

Window::Window()
	: m_glfw_window(nullptr)
{
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::Create(int _width, int _height, const char* _title)
{
	if (glfwInit() != GLFW_TRUE)
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);

	m_glfw_window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
	if (!m_glfw_window)
		return false;

	glfwMakeContextCurrent(m_glfw_window);
	glViewport(0, 0, _width, _height);

	const GLFWvidmode* vid_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(m_glfw_window, (vid_mode->width - _width) / 2, (vid_mode->height - _height) / 2);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return false;

	return true;
}

void Window::ClearBuffers(unsigned int _mask)
{
	glClear(_mask);
}

void Window::SwapBuffers()
{
	assert(m_glfw_window);
	glfwSwapBuffers(m_glfw_window);
}

void Window::Close()
{
	assert(m_glfw_window);
	glfwSetWindowShouldClose(m_glfw_window, GLFW_TRUE);
}

bool Window::isOpen()
{
	assert(m_glfw_window);
	return !glfwWindowShouldClose(m_glfw_window);
}

void Window::SetVsync(bool _vsync)
{
	glfwSwapInterval(_vsync);
}

void Window::SetGlEnable(unsigned int _cap)
{
	glEnable(_cap);
}

void Window::SetGlBlendFunc(unsigned int _sfactor, unsigned int _dfactor)
{
	glBlendFunc(_sfactor, _dfactor);
}

void Window::SetClearColor(float _r, float _g, float _b, float _a)
{
	glClearColor(_r, _g, _b, _a);
}