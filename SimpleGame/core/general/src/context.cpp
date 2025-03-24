#include "general/inc/context.h"

Context::Context(Keyboard& _keyboard, Mouse& _mouse, Cursor& _cursor, MessageBus& _message_bus, Resources& _resources)
	: keyboard(_keyboard)
	, mouse(_mouse)
	, cursor(_cursor)
	, message_bus(_message_bus)
	, resources(_resources)
{
}
