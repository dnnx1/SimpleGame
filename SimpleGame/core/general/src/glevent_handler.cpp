#include "external/GLFW/glfw3.h"
#include "general/inc/glevent_handler.h"

GlEventHandler::GlEventHandler()
	: m_polling(false)
	, m_events()
{
}

bool GlEventHandler::Poll(GlEvent& _event)
{
	m_polling = !m_events.empty();
	if (m_polling)
	{
		_event = m_events.front();
		m_events.pop();
	}

	return m_polling;
}

void GlEventHandler::Send(const GlEvent& _event)
{
	m_events.push(_event);
}

void KeyHandler::Callback(int _key, int _scancode, int _action, int _mods)
{
	if (_key == GLFW_KEY_UNKNOWN) return;
	if (_action != GLFW_PRESS && _action != GLFW_RELEASE) return;

	GlEvent evt;
	evt.type = (_action == GLFW_PRESS ? GlEvent::KeyPressed : GlEvent::KeyReleased);
	evt.data.key.code = _key;
	Send(evt);
}

void MouseButtonHandler::Callback(int _key, int _action, int _mods)
{
	if (_key == GLFW_KEY_UNKNOWN) return;
	if (_action != GLFW_PRESS && _action != GLFW_RELEASE) return;

	GlEvent evt;
	evt.type = (_action == GLFW_PRESS ? GlEvent::MouseButtonPressed: GlEvent::MouseButtonReleased);
	evt.data.mouse_button.code = _key;
	Send(evt);
}

void CursorPosHandler::Callback(double _x, double _y)
{
	GlEvent evt;
	evt.type = GlEvent::CursorMoved;
	evt.data.cursor_pos.x = _x;
	evt.data.cursor_pos.y = _y;
	Send(evt);
}
