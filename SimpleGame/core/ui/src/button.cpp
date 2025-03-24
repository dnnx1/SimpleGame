#include "external/GLFW/glfw3.h"
#include "general/inc/context.h"
#include "resources/inc/resource_manager.h"
#include "ui/inc/button.h"
#include "utility/inc/draw.h"

Button::Button()
	: m_colors()
	, m_texture_id(tx::Undefined)
{
	for (auto& color : m_colors)
		color = glm::vec4(1.0f);
}

bool Button::Create(glm::vec2 _pos, glm::vec2 _size)
{
	SetPosition(_pos);
	SetSize(_size);
	SetMouseButtonCode(GLFW_MOUSE_BUTTON_LEFT);
	return true;
}

void Button::Draw(Resources& _resources)
{
	glm::vec4 color;
	if (isActive()) color = m_colors[cst::Active];
	else if (isHovered()) color = m_colors[cst::Hovered];
	else color = m_colors[cst::Default];

	draw::Sprite(_resources, m_texture_id, GetPosition() + GetSize() / 2.0f, GetSize(), color);
}

void Button::SetColor(cst::id _color_state, glm::vec4 _color)
{
	m_colors[_color_state] = _color;
}

void Button::SetTextureID(tx::id _id)
{
	m_texture_id = _id;
}

bool Button::Check(Context& _context, glm::vec2 _offset)
{
	InternalUpdate(_context, _offset);
	return isClicked();
}
