#include "external/GL/glew.h"
#include "external/glm/gtc/matrix_transform.hpp"
#include "resources/inc/resource_manager.h"
#include "resources/inc/shader.h"
#include "resources/inc/mesh.h"
#include "resources/inc/texture.h"
#include "utility/inc/draw.h"

void draw::Line(Resources& _resources, glm::vec2 _start, glm::vec2 _end, glm::vec4 _col)
{
	glm::mat4 model(1.0f);
	model[3][0] = _start.x;
	model[3][1] = _start.y;

	model[0][0] =  _end.x - _start.x;
	model[1][1] =  _end.y - _start.y;

	_resources.shaders.Get(sh::Primitive).Uniform("u_model", model, true);
	_resources.shaders.Get(sh::Primitive).Uniform("u_color", _col);
	_resources.meshes.Get(msh::Line).Bind(true);
	glDrawArrays(GL_LINES, 0, 2);
	_resources.meshes.Get(msh::Line).Bind(false);
}

void draw::Rect(Resources& _resources, glm::vec2 _center_pos, glm::vec2 _size, glm::vec4 _col, float _angle)
{
	float _cos = cos(glm::radians(_angle));
	float _sin = sin(glm::radians(_angle));

	glm::mat4 model(1.0f);
	model[3][0] = _center_pos.x;
	model[3][1] = _center_pos.y;

	model[0][0] = _cos *_size.x;
	model[1][0] = -_sin *_size.y;
	model[0][1] = _sin * _size.x;
	model[1][1] = _cos * _size.y;

	_resources.shaders.Get(sh::Primitive).Uniform("u_model", model, true);
	_resources.shaders.Get(sh::Primitive).Uniform("u_color", _col);
	_resources.meshes.Get(msh::Rect).Bind(true);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	_resources.meshes.Get(msh::Rect).Bind(false);
}

void draw::Sprite(Resources& _resources, tx::id _id, glm::vec2 _center_pos, glm::vec2 _size, glm::vec4 _col, float _angle)
{
	float _cos = cos(glm::radians(_angle));
	float _sin = sin(glm::radians(_angle));

	glm::mat4 model(1.0f);
	model[3][0] = _center_pos.x;
	model[3][1] = _center_pos.y;

	model[0][0] = _cos * _size.x;
	model[1][0] = -_sin * _size.y;
	model[0][1] = _sin * _size.x;
	model[1][1] = _cos * _size.y;

	_resources.shaders.Get(sh::Sprite).Uniform("u_model", model, true);
	_resources.shaders.Get(sh::Sprite).Uniform("u_color", _col);
	_resources.meshes.Get(msh::Sprite).Bind(true);
	_resources.textures.Get(_id).Bind(true);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	_resources.textures.Get(_id).Bind(false);
	_resources.meshes.Get(msh::Sprite).Bind(false);




}
