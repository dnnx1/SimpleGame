#pragma once
#include <queue>
#include "general/inc/glevent.h"

class GlEventHandler
{
public:
								GlEventHandler();
	virtual						~GlEventHandler() = default;

	bool						Poll(GlEvent& _event);
protected:
	void						Send(const GlEvent& _event);
private:
	bool						m_polling;
	std::queue<GlEvent>			m_events;
};

class IKeyHandler : public GlEventHandler
{
public:
	virtual						~IKeyHandler() = default;

	virtual void				Callback(int _key, int _scancode, int _action, int _mods) = 0;
protected:
private:
};

class KeyHandler : public IKeyHandler
{
public:
	void						Callback(int _key, int _scancode, int _action, int _mods) override;
private:
};

class IMouseButtonHandler : public GlEventHandler
{
public:
	virtual						~IMouseButtonHandler() = default;

	virtual void				Callback(int _key, int _action, int _mods) = 0;
protected:
private:
};

class MouseButtonHandler : public IMouseButtonHandler
{
public:
	void						Callback(int _key, int _action, int _mods) override;
private:
};

class ICursorPosHandler : public GlEventHandler
{
public:
	virtual						~ICursorPosHandler() = default;

	virtual void				Callback(double _x, double _y) = 0;
protected:
private:
};

class CursorPosHandler : public ICursorPosHandler
{
public:
	void						Callback(double _x, double _y) override;
private:
};