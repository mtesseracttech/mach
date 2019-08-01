#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;

in vec3 frag_normal;
in vec3 frag_position;
in mat4 model_view;

out vec4 frag_color;

void main() {
    //Ambient term
    vec3 ambient = material.ambient * light_color;

    //Diffuse term
    vec3 normal = normalize(frag_normal);
    vec3 light = normalize(light_position - frag_position);
    float difference = max(dot(normal, light), 0.0);
    vec3 diffuse = (difference * material.diffuse) * light_color;

    //Specular term
    vec3 view_dir = normalize(camera_position - frag_position);
    vec3 reflect_dir = reflect(-light, normal);
    float specular_strength = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = (specular_strength * material.specular) * light_color;

    vec3 result = (ambient + diffuse + specular) * object_color;
    frag_color = vec4(result, 1.0);
}