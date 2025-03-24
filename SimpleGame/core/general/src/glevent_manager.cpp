#include "external/GLFW/glfw3.h"
#include "general/inc/glevent_manager.h"
#include "general/inc/glevent_handler.h"

GlEventManager::GlEventManager()
	: m_polling(false)
	, m_key_handler(nullptr)
	, m_mouse_button_handler(nullptr)
	, m_cursor_pos_handler(nullptr)
{
}

GlEventManager::~GlEventManager()
{
	if (m_key_handler) delete m_key_handler;
	if (m_mouse_button_handler) delete m_mouse_button_handler;
	if (m_cursor_pos_handler) delete m_cursor_pos_handler;
}

bool GlEventManager::Create()
{
	GLFWwindow* glfw_window = glfwGetCurrentContext();
	if (!glfw_window) return false;
	glfwSetWindowUserPointer(glfw_window, this);
	return true;
}

bool GlEventManager::SetKeyHandler(IKeyHandler* _handler)
{
	GLFWwindow* glfw_window = glfwGetCurrentContext();
	if (!glfw_window || !_handler) return false;
	if (m_key_handler) delete m_key_handler;
	m_key_handler = _handler;

	glfwSetKeyCallback(glfw_window, [](GLFWwindow* _win, int _key, int _scancode, int _action, int _mods)
		{
			auto* manager = (GlEventManager*)glfwGetWindowUserPointer(_win);
			manager->m_key_handler->Callback(_key, _scancode, _action, _mods);
		});

	return true;
}

bool GlEventManager::SetMouseButtonHandler(IMouseButtonHandler* _handler)
{
	GLFWwindow* glfw_window = glfwGetCurrentContext();
	if (!glfw_window || !_handler) return false;
	if (m_mouse_button_handler) delete m_mouse_button_handler;
	m_mouse_button_handler = _handler;

	glfwSetMouseButtonCallback(glfw_window, [](GLFWwindow* _win, int _key, int _action, int _mods)
		{
			auto* manager = (GlEventManager*)glfwGetWindowUserPointer(_win);
			manager->m_mouse_button_handler->Callback(_key, _action, _mods);
		});

	return true;
}

bool GlEventManager::SetCursorPosHandler(ICursorPosHandler* _handler)
{
	GLFWwindow* glfw_window = glfwGetCurrentContext();
	if (!glfw_window || !_handler) return false;
	if (m_cursor_pos_handler) delete m_cursor_pos_handler;
	m_cursor_pos_handler = _handler;

	glfwSetCursorPosCallback(glfw_window, [](GLFWwindow* _win, double _x, double _y)
		{
			auto* manager = (GlEventManager*)glfwGetWindowUserPointer(_win);
			manager->m_cursor_pos_handler->Callback(_x, _y);
		});

	return true;
}

bool GlEventManager::PollEvents(GlEvent& _event)
{
	if (!m_polling) glfwPollEvents();

	if (m_key_handler)
		while (m_key_handler->Poll(_event))
			return m_polling = true;

	if (m_mouse_button_handler)
		while (m_mouse_button_handler->Poll(_event))
			return m_polling = true;

	if (m_cursor_pos_handler)
		while (m_cursor_pos_handler->Poll(_event))
			return m_polling = true;

	return m_polling = false;
}
