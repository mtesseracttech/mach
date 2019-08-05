#version 330 core

out vec4 frag_color;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform vec3 camera_position;
in vec3 frag_normal;
in vec3 frag_position;
in vec2 tex_coords;

void main() {
    vec3 n = normalize(frag_normal);
    vec3 l = normalize(light.position - frag_position);
    float n_dot_l = max(dot(n, l), 0.0); //Light exposure strength
    vec3 view_dir = normalize(camera_position - frag_position);
    vec3 reflect_dir = reflect(-l, n);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse = light.diffuse * n_dot_l * vec3(texture(material.diffuse, tex_coords));

    float specular_strength = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.specular * specular_strength * vec3(texture(material.specular, tex_coords));

    vec3 result = ambient + diffuse + specular;
    frag_color = vec4(result, 1.0);
}