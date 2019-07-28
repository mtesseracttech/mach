#version 330 core

uniform vec3 color;
uniform vec3 light_pos;

out vec4 frag_color;

void main() {
    frag_color = vec4(color, 1.0);
}