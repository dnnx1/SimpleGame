#pragma once
#include "states/pub/st_states.h"

struct Message
{
	enum Type
	{
		CloseApp,
		StateStackPush,
		StateStackPop,
		StateStackClear,
		StateProcess,

	};

	struct CloseAppMsg
	{

	};

	struct StateStackMsg
	{
		st::id					id;
	};

	struct StateProcessMsg
	{
		st::id					id;
		bool					update;
		bool					render;
	};

	union Data
	{
		CloseAppMsg				close_app;
		StateStackMsg			state_stack;
		StateProcessMsg			state_process;
	};

	//////////

	Type						type;
	Data						data;
};