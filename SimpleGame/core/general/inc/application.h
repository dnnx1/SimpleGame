#pragma once
#include "general/inc/window.h"
#include "general/inc/glevent_manager.h"
#include "general/inc/input.h"
#include "general/inc/message_bus.h"
#include "general/inc/context.h"
#include "resources/inc/resource_manager.h"
#include "states/inc/state_stack.h"

class Application
{
	bool						Create();
	bool						CreateShaders();
	bool						CreateMeshes();
	bool						CreateTextures();
	bool						CreateStates();
public:
								Application();

	bool						Run();
private:
	void						HandleEvents();
	void						HandleMessages();
	void						Update(const float& _dt);
	void						Render();

	Window						m_window;
	GlEventManager				m_event_manager;

	Keyboard					m_keyboard;
	Mouse						m_mouse;
	Cursor						m_cursor;
	MessageBus					m_message_bus;
	Resources					m_resources;

	Context						m_context;
	StateStack					m_state_stack;
};