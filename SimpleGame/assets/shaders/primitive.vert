#version 330 core
layout (location = 0) in vec2 i_pos;

uniform mat4 u_proj;
uniform mat4 u_model;

void main()
{
	gl_Position = u_proj * u_model * vec4(i_pos, 0.0, 1.0);
}