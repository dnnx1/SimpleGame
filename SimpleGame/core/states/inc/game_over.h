#pragma once
#include "general/inc/draw_manager.h"
#include "ui/inc/button.h"
#include "states/inc/state.h"

class GameOver : public IState
{
public:
	bool						Create() override;

								GameOver(Context& _context);

	void						HandleMessages(const Message& _msg) override;
	void						Update(const float& _dt) override;
	void						Render() override;
private:
	DrawManager					m_draw_manager;
	Button						m_exit_button;
	glm::vec2					m_window_pos;
};