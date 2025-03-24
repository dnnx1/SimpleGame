#pragma once
#include "general/inc/context.h"

struct Context;
struct Message;

class IState
{
public:
	virtual bool				Create() = 0;

								IState(Context& _context);
	virtual						~IState() = default;

	virtual void				HandleMessages(const Message& _msg) = 0;
	virtual void				Update(const float& _dt) = 0;
	virtual void				Render() = 0;
protected:
	Context&					GetContext();
	Keyboard&					GetKeyboard();
	Mouse&						GetMouse();
	Cursor&						GetCursor();
	MessageBus&					GetMessageBus();
	Resources&					GetResources();
private:
	Context&					m_context;
};