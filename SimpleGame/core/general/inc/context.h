#pragma once

class Keyboard;
class Mouse;
class Cursor;
class MessageBus;
struct Resources;

struct Context
{
								Context(Keyboard& _keyboard, Mouse& _mouse, Cursor& _cursor, MessageBus& _message_bus, Resources& _resources);

	Keyboard&					keyboard;
	Mouse&						mouse;
	Cursor&						cursor;
	MessageBus&					message_bus;
	Resources&					resources;
};