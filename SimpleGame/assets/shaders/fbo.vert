#version 330 core
layout (location = 0) in vec2 i_pos;
layout (location = 1) in vec2 i_tex_coords;

out vec2 io_tex_coords;

uniform mat4 u_proj;
uniform mat4 u_model;

void main()
{
	gl_Position = u_proj * u_model * vec4(i_pos, 0.0f, 1.0);
	io_tex_coords = i_tex_coords;
}