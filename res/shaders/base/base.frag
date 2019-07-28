#version 330 core

in vec3 vert_position;
in vec4 vert_color;
in vec2 vert_tex_coord;

uniform sampler2D texture_diffuse1;

out vec4 frag_color;

void main()
{
    frag_color = texture(texture_diffuse1, vert_tex_coord);
}