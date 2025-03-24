#include <assert.h>
#include "general/inc/message.h"
#include "states/inc/state_stack.h"

StateStack::StateStack(Context& _context)
	: m_context(_context)
	, m_list()
	, m_stack()
{
}

StateStack::~StateStack()
{
	for (auto& elem : m_list)
		if (elem.state) delete elem.state;
}

bool StateStack::Create()
{
	for (auto& elem : m_list)
		if (elem.state)
			if (!elem.state->Create())
				return false;

    return true;
}

void StateStack::HandleMessages(const Message& _msg)
{
	switch (_msg.type)
	{
	case Message::StateStackPush:
		assert(_msg.data.state_stack.id != st::Undefined);
		assert(m_list[_msg.data.state_stack.id].state);
		m_stack.push_back(&m_list[_msg.data.state_stack.id]);
		break;

	case Message::StateStackPop:
		m_stack.pop_back();
		break;

	case Message::StateStackClear:
		m_stack.clear();
		break;

	case Message::StateProcess:
		assert(_msg.data.state_process.id != st::Undefined);
		m_list[_msg.data.state_process.id].update = _msg.data.state_process.update;
		m_list[_msg.data.state_process.id].render = _msg.data.state_process.render;
		break;

	default:
		break;
	}

	for (auto& elem : m_stack)
		if (elem->state)
			elem->state->HandleMessages(_msg);
}

void StateStack::Update(const float& _dt)
{
	for (auto& elem : m_stack)
		if (elem->state && elem->update)
			elem->state->Update(_dt);
}

void StateStack::Render()
{
	for (auto& elem : m_stack)
		if (elem->state && elem->render)
			elem->state->Render();
}

bool StateStack::isEmpty()
{
	return m_stack.empty();
}

StateStack::StateData::StateData()
	: state(nullptr)
	, update(true)
	, render(true)
{
}
