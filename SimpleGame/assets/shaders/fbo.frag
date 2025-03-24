#version 330 core
in vec2 io_tex_coords;

out vec4 o_color;

uniform sampler2D u_texture;
uniform vec4 u_color;

void main()
{
	o_color = u_color * texture(u_texture, io_tex_coords);
}