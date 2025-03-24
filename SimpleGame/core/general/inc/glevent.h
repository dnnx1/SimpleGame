#pragma once

struct GlEvent
{
	enum Type
	{
		Undefined = -1,
		KeyPressed,
		KeyReleased,
		MouseButtonPressed,
		MouseButtonReleased,
		CursorMoved,
	};

	struct KeyEvent
	{
		int						code;
	};

	struct MouseButtonEvent
	{
		int						code;
	};

	struct CursorPosEvent
	{
		double					x;
		double					y;
	};

	union Data
	{
		KeyEvent				key;
		MouseButtonEvent		mouse_button;
		CursorPosEvent			cursor_pos;
	};

	//////////

	Type						type;
	Data						data;
};