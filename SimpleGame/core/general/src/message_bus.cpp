#include "general/inc/message_bus.h"

MessageBus::MessageBus()
	: m_polling(false)
	, m_messages()
	, m_pending_messages()
{
}

bool MessageBus::PollMessages(Message& _msg)
{
	m_polling = !m_messages.empty();
	if (m_polling)
	{
		_msg = m_messages.front();
		m_messages.pop();
	}
	else
	{
		if (!m_pending_messages.empty())
			m_messages.swap(m_pending_messages);
	}

	return m_polling;
}

void MessageBus::Send(const Message& _msg)
{
	m_polling ? m_pending_messages.push(_msg) : m_messages.push(_msg);
}

void MessageBus::SendCloseApp()
{
	Message msg;
	msg.type = Message::CloseApp;
	Send(msg);
}

void MessageBus::SendStateStackPush(st::id _id)
{
	Message msg;
	msg.type = Message::StateStackPush;
	msg.data.state_stack.id = _id;
	Send(msg);
}

void MessageBus::SendStateStackPop()
{
	Message msg;
	msg.type = Message::StateStackPop;
	msg.data.state_stack.id = st::Undefined;
	Send(msg);
}

void MessageBus::SendStateStackClear()
{
	Message msg;
	msg.type = Message::StateStackClear;
	msg.data.state_stack.id = st::Undefined;
	Send(msg);
}

void MessageBus::SendStateProcess(st::id _id, bool _update, bool _render)
{
	Message msg;
	msg.type = Message::StateProcess;
	msg.data.state_process.id = _id;
	msg.data.state_process.update = _update;
	msg.data.state_process.render = _render;
	Send(msg);
}
