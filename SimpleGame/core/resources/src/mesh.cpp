#include <assert.h>
#include "external/GL/glew.h"
#include "resources/inc/mesh.h"

Mesh::Mesh()
	: m_vao(0)
	, m_vbo()
	, m_index(0)
{
}

Mesh::~Mesh()
{
	if (m_vao) glDeleteVertexArrays(1, &m_vao);
	for (auto& vbo : m_vbo)
		if (vbo) glDeleteBuffers(1, &vbo);
}

bool Mesh::Create()
{
	glGenVertexArrays(1, &m_vao);
	return true;
}

int Mesh::AddBuffer(std::vector<int> _attrib_size, bool _instanced)
{
	int idx = (int)m_vbo.size();

	Bind(true);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	int stride = 0;
	for (auto& size : _attrib_size)
		stride += size;
	stride *= sizeof(float);

	int cursor = 0;
	for (auto& size : _attrib_size)
	{
		glVertexAttribPointer(m_index, size, GL_FLOAT, GL_FALSE, stride, (void*)(cursor * sizeof(float)));
		glEnableVertexAttribArray(m_index);
		if (_instanced) glVertexAttribDivisor(m_index, 1);
		++m_index;
		cursor += size;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Bind(false);

	m_vbo.push_back(vbo);
	return idx;
}

void Mesh::UpdateBuffer(int _idx, int _size, void* _data)
{
	assert(_idx >= 0 && _idx < m_vbo.size());
	assert(m_vbo[_idx]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[_idx]);
	glBufferData(GL_ARRAY_BUFFER, _size, _data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Bind(bool _bind)
{
	assert(m_vao);
	glBindVertexArray(_bind ? m_vao : 0);
}
