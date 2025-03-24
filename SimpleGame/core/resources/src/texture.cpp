#include <assert.h>
#include "external/GL/glew.h"
#include "resources/inc/texture.h"

Texture::Texture()
	: m_id(0)
	, m_size(0.0f, 0.0f)
{
}

Texture::~Texture()
{
	if (m_id) glDeleteTextures(1, &m_id);
}

bool Texture::Create(const void* _data, int _width, int _height, int _channels)
{
	glGenTextures(1, &m_id);
	Bind(true);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0,
		_channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, _data);
	Bind(false);

	SetSmooth(false);
	SetRepeat(false);

	return true;
}

void Texture::Bind(bool _bind)
{
	assert(m_id);
	glBindTexture(GL_TEXTURE_2D, _bind ? m_id : 0);
}

void Texture::SetSmooth(bool _smooth)
{
	Bind(true);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _smooth ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _smooth ? GL_LINEAR : GL_NEAREST);
	Bind(false);
}

void Texture::SetRepeat(bool _repeat)
{
	Bind(true);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	Bind(false);
}

unsigned int Texture::GetID()
{
	return m_id;
}

glm::vec2 Texture::GetSize()
{
	return m_size;
}