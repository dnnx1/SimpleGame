template<typename T, typename ...Targs>
inline bool StateStack::AddState(st::id _id, Targs ..._args)
{
	if (m_list[_id].state) delete m_list[_id].state;

	return m_list[_id].state = new T(m_context, _args...);
}