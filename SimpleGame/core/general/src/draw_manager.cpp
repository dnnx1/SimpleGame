#include "external/GLFW/glfw3.h"
#include "external/GL/glew.h"
#include "external/glm/mat4x4.hpp"
#include "external/glm/gtc/matrix_transform.hpp"
#include "general/inc/draw_manager.h"
#include "resources/inc/resource_manager.h"

#include "utility/inc/draw.h"

DrawManager::DrawManager()
	: m_fbo(0)
	, m_fbo_texture()
	, m_fbo_color(1.0f, 1.0f, 1.0f, 1.0f)
	, m_fbo_clear_color(1.0f, 1.0f, 1.0f, 1.0f)
	, m_fbo_pos(0.0f, 0.0f)
	, m_fbo_size(0.0f, 0.0f)
	, m_draw_list()
{
}

DrawManager::~DrawManager()
{
	if (m_fbo) glDeleteFramebuffers(1, &m_fbo);
}

bool DrawManager::Create(glm::vec2 _size)
{
	if (!m_fbo_texture.Create(nullptr, (int)_size.x, (int)_size.y, 4)) return false;
	m_fbo_size = _size;
	
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fbo_texture.GetID(), 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

bool DrawManager::Create(float _x, float _y)
{
	return Create({ _x, _y });
}

void DrawManager::Draw(Resources& _resources, unsigned int _mask)
{
	BeginRender(_resources, _mask);
	for (auto& elem : m_draw_list)
	{
		for (auto& draw_elem : elem.second)
			if (draw_elem) draw_elem->Draw(_resources);
	}

	EndRender(_resources);
	RenderFBO(_resources);
}

void DrawManager::SetColor(glm::vec4 _col)
{
	m_fbo_color = _col;
}

void DrawManager::SetColor(float _r, float _g, float _b, float _a)
{
	SetColor({ _r, _g, _b, _a });
}

void DrawManager::SetClearColor(glm::vec4 _col)
{
	m_fbo_clear_color = _col;
}

void DrawManager::SetClearColor(float _r, float _g, float _b, float _a)
{
	SetClearColor({ _r, _g, _b, _a });
}

void DrawManager::SetPosition(glm::vec2 _pos)
{
	m_fbo_pos = _pos;
}

void DrawManager::SetPosition(float _x, float _y)
{
	SetPosition({ _x, _y });
}

void DrawManager::AddShaderToUpdateProj(sh::id _id, const char* _name)
{
	sprintf(m_proj_update_list[_id], _name);
}

void DrawManager::AddDrawElem(IDrawable* _elem, int _layer)
{
	if (!_elem) return;
	m_draw_list[_layer].push_back(_elem);
}

void DrawManager::RemoveDrawElem(IDrawable* _elem)
{
	if (!_elem) return;
	for (auto& elem : m_draw_list)
		elem.second.remove(_elem);
}

void DrawManager::BeginRender(Resources& _resources, unsigned int _mask)
{
	glViewport(0, 0, (int)m_fbo_size.x, (int)m_fbo_size.y);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glClearColor(m_fbo_clear_color.r, m_fbo_clear_color.g, m_fbo_clear_color.b, m_fbo_clear_color.a);
	glClear(_mask);

	glm::mat4 proj = glm::ortho(0.0f, m_fbo_size.x, m_fbo_size.y, 0.0f);
	for (auto& elem : m_proj_update_list)
		_resources.shaders.Get(elem.first).Uniform(elem.second, proj, true);
}

void DrawManager::EndRender(Resources& _resources)
{
	glViewport(0, 0, 480, 640);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLFWwindow* glfw_window = glfwGetCurrentContext();
	assert(glfw_window);
	int win_width, win_height;
	glfwGetWindowSize(glfw_window, &win_width, &win_height);

	glm::mat4 proj = glm::ortho(0.0f, (float)win_width, (float)win_height, 0.0f);
	for (auto& elem : m_proj_update_list)
		_resources.shaders.Get(elem.first).Uniform(elem.second, proj, true);
}

void DrawManager::RenderFBO(Resources& _resources)
{
	glm::mat4 model(1.0f);
	model[0][0] = m_fbo_size.x;
	model[1][1] = m_fbo_size.y;

	model[3][0] = m_fbo_pos.x;
	model[3][1] = m_fbo_pos.y;

	_resources.shaders.Get(sh::FBO).Uniform("u_model", model, true);
	_resources.shaders.Get(sh::FBO).Uniform("u_color", m_fbo_color);
	_resources.meshes.Get(msh::FBO).Bind(true);
	m_fbo_texture.Bind(true);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_fbo_texture.Bind(false);
	_resources.meshes.Get(msh::FBO).Bind(false);
}
