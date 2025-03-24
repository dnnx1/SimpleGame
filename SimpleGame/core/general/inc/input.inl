#include "input.h"
template<unsigned int Size>
inline IInput<Size>::IInput()
	: m_active_list()
	, m_frame_list()
{
	for (auto& elem : m_active_list)
		elem = false;
	for (auto& elem : m_frame_list)
		elem = 0;
}

template<unsigned int Size>
inline bool IInput<Size>::isClicked(int _code)
{
	if (_code < 0 || _code >= m_active_list.size()) return false;
	return m_active_list[_code];
}

template<unsigned int Size>
inline bool IInput<Size>::isJClicked(int _code)
{
	if (_code < 0 || _code >= m_active_list.size()) return false;
	return m_active_list[_code] && m_frame_list[_code] == GetCurrentFrame();
}

template<unsigned int Size>
inline bool IInput<Size>::isReleased(int _code)
{
	if (_code < 0 || _code >= m_active_list.size()) return false;
	return !m_active_list[_code] && m_frame_list[_code] == GetCurrentFrame();
}

template<unsigned int Size>
inline void IInput<Size>::Set(int _code, bool _active, unsigned int _frame)
{
	assert(_code >= 0 && _code < m_active_list.size());

	m_active_list[_code] = _active;
	m_frame_list[_code] = _frame;
}
