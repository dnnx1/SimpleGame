#pragma once
#include "external/glm/vec4.hpp"
#include "external/glm/vec2.hpp"
#include "resources/pub/tx_textures.h"

class Shader;
class Mesh;
class Texture;
struct Resources;

namespace draw
{
	void Line(Resources& _resources, glm::vec2 _start, glm::vec2 _end, glm::vec4 _col);
	void Rect(Resources& _resources, glm::vec2 _center_pos, glm::vec2 _size, glm::vec4 _col, float _angle = 0.0f);
	void Sprite(Resources& _resources, tx::id _id, glm::vec2 _center_pos, glm::vec2 _size, glm::vec4 _col, float _angle = 0.0f);
}