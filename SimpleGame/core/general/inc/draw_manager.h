#pragma once
#include <map>
#include <list>
#include "external/glm/vec4.hpp"
#include "external/glm/vec2.hpp"
#include "general/inc/drawable.h"
#include "resources/inc/texture.h"
#include "resources/pub/sh_shaders.h"

struct Resources;

class DrawManager
{
public:
								DrawManager();
								~DrawManager();

	bool						Create(glm::vec2 _size);
	bool						Create(float _x, float _y);

	void						Draw(Resources& _resources, unsigned int _mask);

	void						SetColor(glm::vec4 _col);
	void						SetColor(float _r, float _g, float _b, float _a = 1.0f);
	void						SetClearColor(glm::vec4 _col);
	void						SetClearColor(float _r, float _g, float _b, float _a = 1.0f);
	void						SetPosition(glm::vec2 _pos);
	void						SetPosition(float _x, float _y);

	void						AddShaderToUpdateProj(sh::id _id, const char* _name);
	void						AddDrawElem(IDrawable* _elem, int _layer);
	void						RemoveDrawElem(IDrawable* _elem);
private:
	void						BeginRender(Resources& _resources, unsigned int _mask);
	void						EndRender(Resources& _resources);
	void						RenderFBO(Resources& _resources);

	unsigned int				m_fbo;
	Texture						m_fbo_texture;
	glm::vec4					m_fbo_color;
	glm::vec4					m_fbo_clear_color;
	glm::vec2					m_fbo_pos;
	glm::vec2					m_fbo_size;

	std::map<int, std::list<IDrawable*>>	m_draw_list;
	std::map<sh::id, char[256]>				m_proj_update_list;
};