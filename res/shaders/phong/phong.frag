#version 330 core

out vec4 frag_color;

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;

in vec3 frag_normal;
in vec3 frag_position;

in mat4 model_view;

void main() {
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light_color;

    vec3 normal = normalize(frag_normal);
    vec3 light = normalize(light_position - frag_position);
    float difference = max(dot(normal, light), 0.0);
    vec3 diffuse = difference * light_color;

    float specular_strength = 0.5;
    vec3 view_dir = normalize(camera_position - frag_position);
    vec3 reflect_dir = reflect(-light, normal);

    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strength * spec * light_color;

    vec3 result = (ambient + diffuse + specular) * object_color;
    frag_color = vec4(result, 1.0);
}