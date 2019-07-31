#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

out vec3 frag_normal;
out vec3 frag_position;

void main() {
    gl_Position = perspective * view * model * vec4(a_pos, 1.0);
    frag_position = vec3(model * vec4(a_pos, 1.0));
    frag_normal = vec3(model * vec4(a_normal, 1.0));
}
