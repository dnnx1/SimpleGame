#pragma once

struct GLFWwindow;
struct GlEvent;
class IKeyHandler;
class IMouseButtonHandler;
class ICursorPosHandler;

class GlEventManager
{
public:
								GlEventManager();
								~GlEventManager();

	bool						Create();
	bool						SetKeyHandler(IKeyHandler* _handler);
	bool						SetMouseButtonHandler(IMouseButtonHandler* _handler);
	bool						SetCursorPosHandler(ICursorPosHandler* _handler);

	bool						PollEvents(GlEvent& _event);
private:
	bool						m_polling;

	IKeyHandler*				m_key_handler;
	IMouseButtonHandler*		m_mouse_button_handler;
	ICursorPosHandler*			m_cursor_pos_handler;
};