#pragma once
#include <array>
#include <assert.h>
#include "external/glm/vec2.hpp"

struct GlEvent;

class FrameCounter
{
public:
	virtual						~FrameCounter() = default;

	static void					UpdateFrame();
protected:
	unsigned int				GetCurrentFrame();
private:
	static unsigned int			m_frame;
};

template <unsigned int Size>
class IInput : public FrameCounter
{
public:
								IInput();
	virtual						~IInput() = default;

	virtual void				HandleEvents(const GlEvent& _event) = 0;

	bool						isClicked(int _code);
	bool						isJClicked(int _code);
	bool						isReleased(int _code);
protected:
	void						Set(int _code, bool _active, unsigned int _frame);
private:
	std::array<bool, Size>			m_active_list;
	std::array<unsigned int, Size>	m_frame_list;
};

class Keyboard : public IInput<512>
{
public:
	void						HandleEvents(const GlEvent& _event) override;
private:
};

class Mouse : public IInput<16>
{
public:
	void						HandleEvents(const GlEvent& _event) override;
private:
};

class Cursor
{
public:
								Cursor();

	void						HandleEvents(const GlEvent& _event);

	bool						isActive();
	void						Toggle();
	void						Toggle(bool _active);
	glm::vec2					GetLocalPos();
private:
	bool						m_active;
	glm::vec2					m_local_pos;
};

#include "general/inc/input.inl"