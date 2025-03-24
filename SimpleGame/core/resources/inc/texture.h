#pragma once
#include "external/glm/vec2.hpp"

class Texture
{
public:
								Texture();
								~Texture();

	bool						Create(const void* _data, int _width, int _height, int _channels);

	void						Bind(bool _bind);
	void						SetSmooth(bool _smooth);
	void						SetRepeat(bool _repeat);
	unsigned int				GetID();
	glm::vec2					GetSize();
private:
	unsigned int				m_id;
	glm::vec2					m_size;
};