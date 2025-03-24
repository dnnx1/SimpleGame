#include "external/GL/glew.h"
#include "external/GLFW/glfw3.h"
#include "general/inc/message_bus.h"
#include "resources/inc/resource_manager.h"
#include "states/inc/menu_in_game.h"
#include "utility/inc/draw.h"

bool MenuInGame::Create()
{
	GLFWwindow* glfw_window = glfwGetCurrentContext();
	int win_width, win_height;
	glfwGetWindowSize(glfw_window, &win_width, &win_height);

	glm::vec2 window_size(win_width - 120, win_height - 450);

	m_window_pos = { (win_width - window_size.x) / 2.0f, (win_height - window_size.y) / 2.0f };
	m_window_pos.y -= 100.0f;

	if (!m_draw_manager.Create(window_size.x, window_size.y)) return false;
	m_draw_manager.SetPosition(m_window_pos);
	m_draw_manager.SetClearColor(0.8f, 0.8f, 0.8f);
	m_draw_manager.AddShaderToUpdateProj(sh::Sprite, "u_proj");

	glm::vec2 button_size(200.0f, 65.0f);
	glm::vec2 button_pos(0.0f, 0.0f);
	button_pos.x += (window_size.x - button_size.x) / 2.0f;
	button_pos.y += 20.0f;

	m_continue_button.Create(button_pos, button_size);
	m_continue_button.SetTextureID(tx::ButtonContinue);
	m_continue_button.SetColor(cst::Default, { 0.6f, 0.4f, 0.4f, 1.0f });
	m_continue_button.SetColor(cst::Hovered, { 0.8f, 0.6f, 0.6f, 1.0f });
	m_continue_button.SetColor(cst::Active, { 0.7f, 0.5f, 0.5f, 1.0f });

	button_pos.y += (button_size.y + 20.0f);

	m_exit_button.Create(button_pos, button_size);
	m_exit_button.SetTextureID(tx::ButtonExit);
	m_exit_button.SetColor(cst::Default, { 0.6f, 0.4f, 0.4f, 1.0f });
	m_exit_button.SetColor(cst::Hovered, { 0.8f, 0.6f, 0.6f, 1.0f });
	m_exit_button.SetColor(cst::Active, { 0.7f, 0.5f, 0.5f, 1.0f });

	m_draw_manager.AddDrawElem(&m_continue_button, 0);
	m_draw_manager.AddDrawElem(&m_exit_button, 0);

	return true;
}

MenuInGame::MenuInGame(Context& _context)
	: IState(_context)
	, m_continue_button()
	, m_exit_button()
	, m_window_pos(0.0f, 0.0f)
{
}

void MenuInGame::HandleMessages(const Message& _msg)
{
}

void MenuInGame::Update(const float& _dt)
{
	if (m_continue_button.Check(GetContext(), m_window_pos))
	{
		GetMessageBus().SendStateProcess(st::Game, true, true);
		GetMessageBus().SendStateStackPop();
	}

	if (m_exit_button.Check(GetContext(), m_window_pos))
		GetMessageBus().SendCloseApp();
}

void MenuInGame::Render()
{
	m_draw_manager.Draw(GetResources(), GL_COLOR_BUFFER_BIT);
}