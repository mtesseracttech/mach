#version 330 core

out vec4 frag_color;

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_position;

in vec3 frag_normal;
in vec3 frag_position;
in vec3 cam_pos;

//in vec2 frag_tex_coord;
in mat4 model_view;

void main() {
    vec3 l = normalize(frag_position - light_position);
    vec3 r = normalize(reflect(l, frag_normal));
    vec3 v = normalize(frag_position - cam_pos);
    float ambient_strength = dot(v, r);
    vec3 ambient = ambient_strength * light_color;

    vec3 result = ambient * object_color;

    frag_color = vec4(frag_normal, 1.0);
    //frag_color = vec4(result, 1.0);
}
