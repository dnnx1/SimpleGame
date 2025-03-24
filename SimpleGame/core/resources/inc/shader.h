#pragma once
#include "external/glm/mat4x4.hpp"
#include "external/glm/vec4.hpp"
#include "external/glm/vec3.hpp"
#include "external/glm/vec2.hpp"

class Shader
{
public:
								Shader();
								~Shader();

	bool						Create(const char* _vert, const char* _frag, const char* _geom = nullptr);

	void						Use();
	void						Uniform(const char* _name, const glm::mat4& _matrix, bool _use_shader = false);
	void						Uniform(const char* _name, const glm::vec4& _vec, bool _use_shader = false);
	void						Uniform(const char* _name, const float& _x, const float& _y, const float& _z, const float& _w, bool _use_shader = false);
	void						Uniform(const char* _name, const glm::vec3& _vec, bool _use_shader = false);
	void						Uniform(const char* _name, const float& _x, const float& _y, const float& _z, bool _use_shader = false);
	void						Uniform(const char* _name, const glm::vec2& _vec, bool _use_shader = false);
	void						Uniform(const char* _name, const float& _x, const float& _y, bool _use_shader = false);
	void						Uniform(const char* _name, const float& _val, bool _use_shader = false);
	void						Uniform(const char* _name, const int& _val, bool _use_shader = false);
private:
	unsigned int				m_id;
};