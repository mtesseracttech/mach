#version 330 core

in vec3 vert_position;
in vec4 vert_color;
in vec2 vert_tex_coord;

uniform sampler2D test_texture;
uniform vec3 test_color;

out vec4 frag_color;

void main()
{
    //    fragColor = vec4(frag_position, 1.0);
    //    fragColor = vertColor * ourColor;
    //    fragColor = ourColor;

    frag_color = texture(test_texture, vert_tex_coord);// * vec4(test_color, 1.0);
}