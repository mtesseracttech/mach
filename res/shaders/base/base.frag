#version 330 core
out vec4 fragColor;
in vec4 vertColor;

uniform vec4 ourColor;
in vec3 testPosition;


void main()
{
    //    fragColor = vec4(testPosition, 1.0);
    fragColor = vertColor * ourColor;
    //    fragColor = ourColor;
}