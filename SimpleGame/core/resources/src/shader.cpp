#include <assert.h>
#include <cstdio>
#include "external/GL/glew.h"
#include "external/glm/gtc/type_ptr.hpp"
#include "resources/inc/shader.h"

#define BUFFER_SIZE				512

static unsigned int GenerateShader(const char* _source, unsigned int _type, int& _success)
{
	unsigned int id;
	id = glCreateShader(_type);
	glShaderSource(id, 1, &_source, nullptr);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &_success);
	return id;
}

#ifdef _DEBUG
static void PrintLog(const char* _msg, const char* _log)
{
	printf("%s\n%s\n", _msg, _log);
}
#endif

Shader::Shader()
	: m_id(0)
{
}

Shader::~Shader()
{
	if (m_id) glDeleteProgram(m_id);
}

bool Shader::Create(const char* _vert, const char* _frag, const char* _geom)
{
	int success;
#ifdef _DEBUG
	char log[BUFFER_SIZE];
#endif

	unsigned int vert_shader;
	vert_shader = GenerateShader(_vert, GL_VERTEX_SHADER, success);
	if (!success)
	{
#ifdef _DEBUG
		glGetShaderInfoLog(vert_shader, BUFFER_SIZE, nullptr, log);
		PrintLog("Cant compile vertex shader", log);
#endif
		return false;
	}

	unsigned int frag_shader;
	frag_shader = GenerateShader(_frag, GL_FRAGMENT_SHADER, success);
	if (!success)
	{
#ifdef _DEBUG
		glGetShaderInfoLog(frag_shader, BUFFER_SIZE, nullptr, log);
		PrintLog("Cant compile fragment shader", log);
#endif
		glDeleteShader(vert_shader);
		return false;
	}

	unsigned int geom_shader;
	if (_geom)
	{
		geom_shader = GenerateShader(_geom, GL_GEOMETRY_SHADER, success);
		if (!success)
		{
#ifdef _DEBUG
			glGetShaderInfoLog(geom_shader, BUFFER_SIZE, nullptr, log);
			PrintLog("Cant compile geomentry shader", log);
#endif
			glDeleteShader(vert_shader);
			glDeleteShader(frag_shader);
			return false;
		}
	}

	m_id = glCreateProgram();
	glAttachShader(m_id, vert_shader);
	glAttachShader(m_id, frag_shader);
	if (_geom) glAttachShader(m_id, geom_shader);
	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
#ifdef _DEBUG
		glGetProgramInfoLog(m_id, BUFFER_SIZE, nullptr, log);
		PrintLog("Cant link program", log);
#endif
		glDeleteShader(vert_shader);
		glDeleteShader(frag_shader);
		if (_geom) glDeleteShader(geom_shader);
		return false;
	}

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
	if (_geom) glDeleteShader(geom_shader);
	return true;
}

void Shader::Use()
{
	assert(m_id);
	glUseProgram(m_id);
}

void Shader::Uniform(const char* _name, const glm::mat4& _matrix, bool _use_shader)
{
	if (_use_shader) Use();
	glUniformMatrix4fv(glGetUniformLocation(m_id, _name), 1, GL_FALSE, glm::value_ptr(_matrix));
}

void Shader::Uniform(const char* _name, const glm::vec4& _vec, bool _use_shader)
{
	if (_use_shader) Use();
	glUniform4f(glGetUniformLocation(m_id, _name), _vec.x, _vec.y, _vec.z, _vec.w);
}

void Shader::Uniform(const char* _name, const float& _x, const float& _y, const float& _z, const float& _w, bool _use_shader)
{
	Uniform(_name, { _x, _y, _z, _w }, _use_shader);
}

void Shader::Uniform(const char* _name, const glm::vec3& _vec, bool _use_shader)
{
	if (_use_shader) Use();
	glUniform3f(glGetUniformLocation(m_id, _name), _vec.x, _vec.y, _vec.z);
}

void Shader::Uniform(const char* _name, const float& _x, const float& _y, const float& _z, bool _use_shader)
{
	Uniform(_name, { _x, _y, _z }, _use_shader);
}

void Shader::Uniform(const char* _name, const glm::vec2& _vec, bool _use_shader)
{
	if (_use_shader) Use();
	glUniform2f(glGetUniformLocation(m_id, _name), _vec.x, _vec.y);
}

void Shader::Uniform(const char* _name, const float& _x, const float& _y, bool _use_shader)
{
	Uniform(_name, { _x, _y }, _use_shader);
}

void Shader::Uniform(const char* _name, const float& _val, bool _use_shader)
{
	if (_use_shader) Use();
	glUniform1f(glGetUniformLocation(m_id, _name), _val);
}

void Shader::Uniform(const char* _name, const int& _val, bool _use_shader)
{
	if (_use_shader) Use();
	glUniform1i(glGetUniformLocation(m_id, _name), _val);
}