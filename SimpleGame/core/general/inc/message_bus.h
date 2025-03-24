#pragma once
#include <queue>
#include "general/inc/message.h"
#include "states/pub/st_states.h"

class MessageBus
{
public:
								MessageBus();

	bool						PollMessages(Message& _msg);
	void						Send(const Message& _msg);

	void						SendCloseApp();
	void						SendStateStackPush(st::id _id);
	void						SendStateStackPop();
	void						SendStateStackClear();
	void						SendStateProcess(st::id _id, bool _update, bool _render);
private:
	bool						m_polling;

	std::queue<Message>			m_messages;
	std::queue<Message>			m_pending_messages;
};