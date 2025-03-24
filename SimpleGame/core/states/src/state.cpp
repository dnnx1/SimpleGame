#include "states/inc/state.h"

IState::IState(Context& _context)
	: m_context(_context)
{
}

Context& IState::GetContext()
{
	return m_context;
}

Keyboard& IState::GetKeyboard()
{
	return m_context.keyboard;
}

Mouse& IState::GetMouse()
{
	return m_context.mouse;
}

Cursor& IState::GetCursor()
{
	return m_context.cursor;
}

MessageBus& IState::GetMessageBus()
{
	return m_context.message_bus;
}

Resources& IState::GetResources()
{
	return m_context.resources;
}
