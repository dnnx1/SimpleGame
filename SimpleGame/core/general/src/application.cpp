#include "external/GL/glew.h"
#include "external/GLFW/glfw3.h"
#include "external/glm/gtc/matrix_transform.hpp"
#include "general/inc/application.h"
#include "general/inc/glevent_handler.h"
#include "general/inc/clock.h"
#include "states/inc/menu_main.h"
#include "states/inc/menu_in_game.h"
#include "states/inc/game.h"
#include "states/inc/game_over.h"

bool Application::Create()
{
	if (!m_window.Create(480, 640, "SimpleGame")) return false;
	m_window.SetVsync(true);
	m_window.SetGlEnable(GL_BLEND);
	m_window.SetGlBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_window.SetClearColor(1.0f, 1.0f, 1.0f);

	if (!m_event_manager.Create()) return false;
	if (!m_event_manager.SetKeyHandler(new KeyHandler())) return false;
	if (!m_event_manager.SetMouseButtonHandler(new MouseButtonHandler())) return false;
	if (!m_event_manager.SetCursorPosHandler(new CursorPosHandler())) return false;

	if (!CreateShaders()) return false;
	if (!CreateMeshes()) return false;
	if (!CreateTextures()) return false;

	if (!CreateStates()) return false;

	return true;
}

bool Application::CreateShaders()
{
	auto& shaders = m_resources.shaders;
	GLFWwindow* glfw_window = glfwGetCurrentContext();
	int win_width, win_height;
	glfwGetWindowSize(glfw_window, &win_width, &win_height);

	glm::mat4 proj = glm::ortho(0.0f, (float)win_width, (float)win_height, 0.0f);

	if (!shaders.LoadFromFile(sh::Primitive, "./assets/shaders/primitive.vert", "./assets/shaders/primitive.frag")) return false;
	shaders.Get(sh::Primitive).Uniform("u_proj", proj, true);

	if (!shaders.LoadFromFile(sh::FBO, "./assets/shaders/fbo.vert", "./assets/shaders/fbo.frag")) return false;
	shaders.Get(sh::FBO).Uniform("u_proj", proj, true);
	shaders.Get(sh::FBO).Uniform("u_texture", 0);

	if (!shaders.LoadFromFile(sh::Sprite, "./assets/shaders/sprite.vert", "./assets/shaders/sprite.frag")) return false;
	shaders.Get(sh::Sprite).Uniform("u_proj", proj, true);
	shaders.Get(sh::Sprite).Uniform("u_texture", 0);

	return true;
}

bool Application::CreateMeshes()
{
	auto& meshes = m_resources.meshes;

	float line_buff[] =
	{
		// pos
		+0.0f, +0.0f,
		+1.0f, +1.0f,
	};
	float rect_buff[] =
	{
		// pos
		-0.5f, -0.5f,
		+0.5f, -0.5f,
		+0.5f, +0.5f,
		-0.5f, +0.5f,
	};
	float fbo_buff[] =
	{
		// pos				// tex_coords
		+0.0f, +0.0f,		0.0f, 1.0f,
		+1.0f, +0.0f,		1.0f, 1.0f,
		+1.0f, +1.0f,		1.0f, 0.0f,

		+0.0f, +0.0f,		0.0f, 1.0f,
		+1.0f, +1.0f,		1.0f, 0.0f,
		+0.0f, +1.0f,		0.0f, 0.0f,
	};
	float sprite_buff[] =
	{
		// pos				// tex_coords
		-0.5f, -0.5f,		0.0f, 1.0f,
		+0.5f, -0.5f,		1.0f, 1.0f,
		+0.5f, +0.5f,		1.0f, 0.0f,

		-0.5f, -0.5f,		0.0f, 1.0f,
		+0.5f, +0.5f,		1.0f, 0.0f,
		-0.5f, +0.5f,		0.0f, 0.0f,
	};
	//////////

	if (!meshes.Create(msh::Line)) return false;
	meshes.Get(msh::Line).UpdateBuffer(meshes.Get(msh::Line).AddBuffer({ 2, }, false), sizeof(line_buff), line_buff);

	if (!meshes.Create(msh::Rect)) return false;
	meshes.Get(msh::Rect).UpdateBuffer(meshes.Get(msh::Rect).AddBuffer({ 2, }, false), sizeof(rect_buff), rect_buff);

	if (!meshes.Create(msh::FBO)) return false;
	meshes.Get(msh::FBO).UpdateBuffer(meshes.Get(msh::FBO).AddBuffer({ 2, 2, }, false), sizeof(fbo_buff), fbo_buff);

	if (!meshes.Create(msh::Sprite)) return false;
	meshes.Get(msh::Sprite).UpdateBuffer(meshes.Get(msh::Sprite).AddBuffer({ 2, 2, }, false), sizeof(sprite_buff), sprite_buff);

	return true;
}

bool Application::CreateTextures()
{
	auto& textures = m_resources.textures;

	if (!textures.LoadFromFile(tx::ButtonStart, "./assets/images/button_start.png")) return false;
	if (!textures.LoadFromFile(tx::ButtonExit, "./assets/images/button_exit.png")) return false;
	if (!textures.LoadFromFile(tx::ButtonContinue, "./assets/images/button_continue.png")) return false;
	if (!textures.LoadFromFile(tx::Circle, "./assets/images/circle.png")) return false;
	if (!textures.LoadFromFile(tx::Box, "./assets/images/box.png")) return false;

	return true;
}

bool Application::CreateStates()
{
	if (!m_state_stack.AddState<MenuMain>(st::MenuMain)) return false;
	if (!m_state_stack.AddState<MenuInGame>(st::MenuInGame)) return false;
	if (!m_state_stack.AddState<Game>(st::Game)) return false;
	if (!m_state_stack.AddState<GameOver>(st::GameOver)) return false;

	if (!m_state_stack.Create()) return false;

	m_message_bus.SendStateStackPush(st::MenuMain);
	return true;
}

Application::Application()
	: m_window()
	, m_mouse()
	, m_cursor()
	, m_message_bus()
	, m_resources()
	, m_context(m_keyboard, m_mouse, m_cursor, m_message_bus, m_resources)
	, m_state_stack(m_context)
{
}

bool Application::Run()
{
	if (!Create()) return false;

	Clock clock;
	clock.GetElapsed();
	while (m_window.isOpen())
	{
		HandleEvents();
		HandleMessages();
		Update(clock.GetElapsed());
		Render();
		if (m_state_stack.isEmpty())
			m_window.Close();
	}

	return true;
}

void Application::HandleEvents()
{
	FrameCounter::UpdateFrame();
	GlEvent evt;
	while (m_event_manager.PollEvents(evt))
	{
		m_keyboard.HandleEvents(evt);
		m_mouse.HandleEvents(evt);
		m_cursor.HandleEvents(evt);
	}
}

void Application::HandleMessages()
{
	Message msg;
	while (m_message_bus.PollMessages(msg))
	{
		switch (msg.type)
		{
		case Message::CloseApp:
			m_window.Close();
			break;

		default:
			break;
		}

		m_state_stack.HandleMessages(msg);
	}
}

void Application::Update(const float& _dt)
{
	m_state_stack.Update(_dt);
}

void Application::Render()
{
	m_window.ClearBuffers(GL_COLOR_BUFFER_BIT);
	m_state_stack.Render();
	m_window.SwapBuffers();
}
