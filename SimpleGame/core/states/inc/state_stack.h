#pragma once
#include <array>
#include <vector>
#include "states/inc/state.h"
#include "states/pub/st_states.h"

struct Context;
struct Message;

class StateStack
{
public:
								StateStack(Context& _context);
								~StateStack();

	bool						Create();

	void						HandleMessages(const Message& _msg);
	void						Update(const float& _dt);
	void						Render();

	bool						isEmpty();

	template <typename T, typename ...Targs>
	bool						AddState(st::id _id, Targs ..._args);
private:
	struct StateData
	{
								StateData();

		IState*					state;
		bool					update;
		bool					render;
	};

	Context&					m_context;

	std::array<StateData, st::__count>	m_list;
	std::vector<StateData*>				m_stack;
};

#include "states/inc/state_stack.inl"