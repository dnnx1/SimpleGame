#include <cstring>
#include "external/GLFW/glfw3.h"
#include "general/inc/input.h"
#include "general/inc/glevent.h"

unsigned int FrameCounter::m_frame = 0;

void FrameCounter::UpdateFrame()
{
	++m_frame;
}

unsigned int FrameCounter::GetCurrentFrame()
{
	return m_frame;
}

void Keyboard::HandleEvents(const GlEvent& _event)
{
	switch (_event.type)
	{
	case GlEvent::KeyPressed:
		Set(_event.data.key.code, true, GetCurrentFrame());
		break;

	case GlEvent::KeyReleased:
		Set(_event.data.key.code, false, GetCurrentFrame());
		break;

	default:
		break;
	}
}

void Mouse::HandleEvents(const GlEvent& _event)
{
	switch (_event.type)
	{
	case GlEvent::MouseButtonPressed:
		Set(_event.data.mouse_button.code, true, GetCurrentFrame());
		break;

	case GlEvent::MouseButtonReleased:
		Set(_event.data.mouse_button.code, false, GetCurrentFrame());
		break;

	default:
		break;
	}
}

Cursor::Cursor()
	: m_active(true)
	, m_local_pos(0.0f, 0.0f)
{
}

void Cursor::HandleEvents(const GlEvent& _event)
{
	if (_event.type == GlEvent::CursorMoved && m_active)
	{
		m_local_pos.x = (float)_event.data.cursor_pos.x;
		m_local_pos.y = (float)_event.data.cursor_pos.y;
	}
}

bool Cursor::isActive()
{
	return m_active;
}

void Cursor::Toggle()
{
	Toggle(!m_active);
}

void Cursor::Toggle(bool _active)
{
	GLFWwindow* glfw_window = glfwGetCurrentContext();
	assert(glfw_window);
	m_active = _active;
	glfwSetInputMode(glfw_window, GLFW_CURSOR,
		m_active ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

glm::vec2 Cursor::GetLocalPos()
{
	return m_local_pos;
}
