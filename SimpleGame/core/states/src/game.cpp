#include "external/GL/glew.h"
#include "external/GLFW/glfw3.h"
#include "general/inc/message_bus.h"
#include "general/inc/input.h"
#include "resources/inc/resource_manager.h"
#include "states/inc/game.h"
#include "utility/inc/draw.h"

bool Game::Create()
{
	GLFWwindow* glfw_window = glfwGetCurrentContext();
	int win_width, win_height;
	glfwGetWindowSize(glfw_window, &win_width, &win_height);
	glm::vec2 window_size(win_width, win_height);

	if (!m_draw_manager.Create(window_size.x, window_size.y)) return false;
	m_draw_manager.SetClearColor(0.8f, 0.8f, 0.8f);

	m_player.SetPosition((win_width - 50.0f) / 2.0f, win_height - 50.0f);
	m_player.SetSize(50.0f);
	m_player.SetColor(0.8f, 0.2f, 0.1f);

	m_player.SetBoxPosition((win_width - 32.0f) / 2.0f, win_height - 32.0f - 40.0f);
	m_player.SetBoxSize(32.0f);
	m_player.SetBoxColor(1.0f, 1.0f, 1.0f);

	m_draw_manager.AddDrawElem(&m_player, 0);

	return true;
}

Game::Game(Context& _context)
	: IState(_context)
{
}

void Game::HandleMessages(const Message& _msg)
{
	if (_msg.type == Message::StateProcess)
	{
		if (_msg.data.state_process.id == st::Game)
		{
			if (_msg.data.state_process.update)
				m_draw_manager.SetColor(1.0f, 1.0f, 1.0f);
			else
				m_draw_manager.SetColor(0.5f, 0.5f, 0.5f);
		}
	}
}

void Game::Update(const float& _dt)
{
	if (GetKeyboard().isJClicked(GLFW_KEY_ESCAPE))
	{
		GetMessageBus().SendStateProcess(st::Game, false, true);
		GetMessageBus().SendStateStackPush(st::MenuInGame);
	}

	if (GetKeyboard().isClicked(GLFW_KEY_A))
		m_player.Move(-210.0f * _dt);
	if (GetKeyboard().isClicked(GLFW_KEY_D))
		m_player.Move(210.0f * _dt);

	m_spawner.Prepare();

	Enemy* enemy = m_spawner.Create(_dt);
	if (enemy)
		m_draw_manager.AddDrawElem(enemy, 0);

	m_spawner.MovementProcess(_dt);

	GLFWwindow* glfw_window = glfwGetCurrentContext();
	int win_width, win_height;
	glfwGetWindowSize(glfw_window, &win_width, &win_height);

	for (auto& enemy : m_spawner.GetList())
	{
		if (m_player.CheckCollision(*enemy))
		{
			m_spawner.Remove(enemy);
			m_draw_manager.RemoveDrawElem(enemy);
		}

		if (enemy->GetPosition().y > (float)win_height)
		{
			GetMessageBus().SendStateProcess(st::Game, false, true);
			GetMessageBus().SendStateStackPush(st::GameOver);
			break;
		}
	}
}

void Game::Render()
{
	m_draw_manager.Draw(GetResources(), GL_COLOR_BUFFER_BIT);
}
