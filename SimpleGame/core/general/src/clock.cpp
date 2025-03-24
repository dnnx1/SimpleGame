#include "external/GLFW/glfw3.h"
#include "general/inc/clock.h"

Clock::Clock()
	: m_start(0.0)
{
}

float Clock::GetElapsed()
{
	float curr = (float)glfwGetTime();
	float elapsed = curr - m_start;
	m_start = curr;
	return elapsed;
}
