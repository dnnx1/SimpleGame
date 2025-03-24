#pragma once
#include <array>
#include "general/inc/drawable.h"
#include "resources/pub/tx_textures.h"
#include "ui/inc/invisible_button.h"
#include "ui/pub/cst_color_states.h"

class Button : public InvisibleButton, public IDrawable
{
public:
								Button();

	bool						Create(glm::vec2 _pos, glm::vec2 _size);

	void						Draw(Resources& _resources) override;
	void						SetColor(cst::id _color_state, glm::vec4 _color);
	void						SetTextureID(tx::id _id);

	bool						Check(Context& _context, glm::vec2 _offset = glm::vec2(0.0, 0.0f));
private:
	std::array<glm::vec4, cst::__count>	m_colors;
	tx::id								m_texture_id;
};