#include "external/GLFW/glfw3.h"
#include "general/inc/context.h"
#include "general/inc/input.h"
#include "ui/inc/invisible_button.h"

InvisibleButton::InvisibleButton()
	: m_mouse_button_code(GLFW_KEY_UNKNOWN)
	, m_position(0.0f, 0.0f)
	, m_size(0.0f, 0.0f)
	, m_hovered(false)
	, m_active(false)
	, m_clicked(false)
{
}

void InvisibleButton::SetPosition(glm::vec2 _pos)
{
	m_position = _pos;
}

void InvisibleButton::SetPosition(float _x, float _y)
{
	SetPosition({ _x, _y });
}

void InvisibleButton::SetSize(glm::vec2 _size)
{
	m_size = _size;
}

void InvisibleButton::SetSize(float _x, float _y)
{
	SetSize({ _x, _y });
}

void InvisibleButton::SetMouseButtonCode(int _code)
{
	m_mouse_button_code = _code;
}

glm::vec2 InvisibleButton::GetPosition()
{
    return m_position;
}

glm::vec2 InvisibleButton::GetSize()
{
	return m_size;
}

bool InvisibleButton::isHovered()
{
	return m_hovered;
}

bool InvisibleButton::isClicked()
{
	return m_clicked;
}

bool InvisibleButton::isActive()
{
	return m_active;
}

void InvisibleButton::InternalUpdate(Context& _context, glm::vec2 _offset)
{
	bool cursor_active = _context.cursor.isActive();
	glm::vec2 cursor_pos = _context.cursor.GetLocalPos();
	glm::vec2 point_min = m_position + _offset;
	glm::vec2 point_max = m_position + m_size + _offset;

	m_hovered = (point_min.x <= cursor_pos.x && point_max.x >= cursor_pos.x &&
		point_min.y <= cursor_pos.y && point_max.y >= cursor_pos.y && cursor_active);

	if (m_active)
	{
		m_active = _context.mouse.isClicked(m_mouse_button_code) && cursor_active;
		m_clicked = _context.mouse.isReleased(m_mouse_button_code) && cursor_active && m_hovered;
	}
	else
	{
		m_active = _context.mouse.isJClicked(m_mouse_button_code) && cursor_active && m_hovered;
		m_clicked = false;
	}
}