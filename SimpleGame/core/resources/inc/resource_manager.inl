template<typename ID, typename T, int Size>
inline ResourceManager<ID, T, Size>::ResourceManager()
	: m_list()
{
	for (auto& elem : m_list)
		elem = nullptr;
}

template<typename ID, typename T, int Size>
inline ResourceManager<ID, T, Size>::~ResourceManager()
{
	for (auto& elem : m_list)
		if (elem) delete elem;
}

template<typename ID, typename T, int Size>
inline T& ResourceManager<ID, T, Size>::Get(ID _id)
{
	assert(m_list[_id]);
	return *m_list[_id];
}

template<typename ID, typename T, int Size>
inline void ResourceManager<ID, T, Size>::Push(ID _id, T* _res)
{
	if (m_list[_id]) delete m_list[_id];
	m_list[_id] = _res;
}
