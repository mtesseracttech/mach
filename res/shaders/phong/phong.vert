#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
//layout (location = 2) in vec2 a_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

out vec3 frag_normal;
out vec3 frag_position;
//out vec2 frag_tex_coord;
out mat4 model_view;
out vec3 cam_pos;

void main() {
    cam_pos = view[3].xyz;
    model_view = view * model;
    frag_normal = (model_view * vec4(a_normal, 1.0)).xyz;
    frag_position = (model_view * vec4(a_pos, 1.0)).xyz;
    gl_Position = perspective * model_view * vec4(a_pos, 1.0);
}
