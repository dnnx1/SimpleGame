#include "external/GL/glew.h"
#include "external/GLFW/glfw3.h"
#include "general/inc/message_bus.h"
#include "resources/inc/resource_manager.h"
#include "states/inc/menu_main.h"
#include "utility/inc/draw.h"

bool MenuMain::Create()
{
	GLFWwindow* glfw_window = glfwGetCurrentContext();
	int win_width, win_height;
	glfwGetWindowSize(glfw_window, &win_width, &win_height);
	glm::vec2 window_size(win_width, win_height);

	if (!m_draw_manager.Create(window_size.x, window_size.y)) return false;
	m_draw_manager.SetClearColor(0.8f, 0.8f, 0.8f);

	glm::vec2 button_size(300.0f, 100.0f);
	glm::vec2 button_pos(0.0f, 0.0f);
	button_pos.x += (window_size.x - button_size.x) / 2.0f;
	button_pos.y += 180.0f;

	m_play_button.Create(button_pos, button_size);
	m_play_button.SetTextureID(tx::ButtonStart);
	m_play_button.SetColor(cst::Default, { 0.6f, 0.4f, 0.4f, 1.0f });
	m_play_button.SetColor(cst::Hovered, { 0.8f, 0.6f, 0.6f, 1.0f });
	m_play_button.SetColor(cst::Active, { 0.7f, 0.5f, 0.5f, 1.0f });

	button_pos.y += (button_size.y + 50.0f);

	m_exit_button.Create(button_pos, button_size);
	m_exit_button.SetTextureID(tx::ButtonExit);
	m_exit_button.SetColor(cst::Default, { 0.6f, 0.4f, 0.4f, 1.0f });
	m_exit_button.SetColor(cst::Hovered, { 0.8f, 0.6f, 0.6f, 1.0f });
	m_exit_button.SetColor(cst::Active, { 0.7f, 0.5f, 0.5f, 1.0f });

	m_draw_manager.AddDrawElem(&m_play_button, 0);
	m_draw_manager.AddDrawElem(&m_exit_button, 0);

	return true;
}

MenuMain::MenuMain(Context& _context)
	: IState(_context)
{
}

void MenuMain::HandleMessages(const Message& _msg)
{
}

void MenuMain::Update(const float& _dt)
{
	if (m_play_button.Check(GetContext()))
	{
		GetMessageBus().SendStateStackClear();
		GetMessageBus().SendStateStackPush(st::Game);
	}

	if (m_exit_button.Check(GetContext()))
		GetMessageBus().SendCloseApp();
}

void MenuMain::Render()
{
	m_draw_manager.Draw(GetResources(), GL_COLOR_BUFFER_BIT);
}
