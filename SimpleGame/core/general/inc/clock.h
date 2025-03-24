#pragma once

class Clock
{
public:
								Clock();

	float						GetElapsed();
private:
	float						m_start;
};