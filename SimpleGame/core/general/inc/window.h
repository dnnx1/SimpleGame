#pragma once

struct GLFWwindow;

class Window
{
public:
								Window();
								~Window();

	bool						Create(int _width, int _height, const char* _title);

	void						ClearBuffers(unsigned int _mask);
	void						SwapBuffers();
	void						Close();
	bool						isOpen();

	void						SetVsync(bool _vsync);
	void						SetGlEnable(unsigned int _cap);
	void						SetGlBlendFunc(unsigned int _sfactor, unsigned int _dfactor);
	void						SetClearColor(float _r, float _g, float _b, float _a = 1.0f);
private:
	GLFWwindow*					m_glfw_window;
};