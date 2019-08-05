#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

out vec3 vert_color;
out vec3 vert_position;
out vec2 vert_tex_coord;

void main()
{
    mat4 mvp = perspective * view * model;

    vert_color = a_color;
    vert_position = a_pos;
    vert_tex_coord = a_tex_coord;
    gl_Position = mvp * vec4(a_pos, 1.0);
}