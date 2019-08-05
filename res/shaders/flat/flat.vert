#version 330 core
layout (location = 0) in vec3 a_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

void main()
{
    mat4 mvp = perspective * view * model;
    gl_Position = mvp * vec4(a_pos, 1.0);
}