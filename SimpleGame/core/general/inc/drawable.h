#pragma once

struct Resources;

class IDrawable
{
public:
	virtual void				Draw(Resources& _resources) = 0;
protected:
private:
};