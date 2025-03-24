#pragma once
#include "external/glm/vec4.hpp"
#include "external/glm/vec2.hpp"

struct Context;

class InvisibleButton
{
public:
								InvisibleButton();
	virtual						~InvisibleButton() = default;

protected:
	void						SetPosition(glm::vec2 _pos);
	void						SetPosition(float _x, float _y);
	void						SetSize(glm::vec2 _size);
	void						SetSize(float _x, float _y);
	void						SetMouseButtonCode(int _code);

	glm::vec2					GetPosition();
	glm::vec2					GetSize();

	bool						isHovered();
	bool						isClicked();
	bool						isActive();

	void						InternalUpdate(Context& _context, glm::vec2 _offset);
private:
	int							m_mouse_button_code;
	glm::vec2					m_position;
	glm::vec2					m_size;

	bool						m_hovered;
	bool						m_active;
	bool						m_clicked;
};