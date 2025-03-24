#pragma once
#include "general/inc/draw_manager.h"
#include "states/inc/state.h"
#include "units/inc/unit.h"

class Game : public IState
{
public:
	bool						Create() override;

								Game(Context& _context);

	void						HandleMessages(const Message& _msg) override;
	void						Update(const float& _dt) override;
	void						Render() override;
private:
	DrawManager					m_draw_manager;
	Player						m_player;
	EnemySpawner				m_spawner;
};