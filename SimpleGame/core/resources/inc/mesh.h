#pragma once
#include <vector>

class Mesh
{
public:
								Mesh();
								~Mesh();

	bool						Create();

	int							AddBuffer(std::vector<int> _attrib_size, bool _instanced);
	void						UpdateBuffer(int _idx, int _size, void* _data);
	void						Bind(bool _bind);
private:
	unsigned int				m_vao;
	std::vector<unsigned int>	m_vbo;

	unsigned int				m_index;
};