#version 330 core

out vec4 frag_color;

in vec3 vert_color;
in vec3 vert_position;
in vec2 vert_tex_coord;

void main() {

    vec3 light_position = vec3(1.0,1.0,1.0);

    vec3 light_color = vec3(1.0, 1.0, 1.0);
    vec3 object_color = vec3(1.0, 0.5, 0.25);

    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light_color;

    vec3 result = ambient * object_color;


    frag_color = vec4(result, 1.0);
}
