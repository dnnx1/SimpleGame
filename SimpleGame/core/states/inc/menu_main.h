#pragma once
#include "general/inc/draw_manager.h"
#include "ui/inc/button.h"
#include "states/inc/state.h"

class MenuMain : public IState
{
public:
	bool						Create() override;

								MenuMain(Context& _context);

	void						HandleMessages(const Message& _msg) override;
	void						Update(const float& _dt) override;
	void						Render() override;
private:
	DrawManager					m_draw_manager;
	Button						m_play_button;
	Button						m_exit_button;
};