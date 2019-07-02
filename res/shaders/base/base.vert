#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertColor;
//uniform float offset;
out vec3 testPosition;

void main()
{
    vertColor = aColor;
    //vec3 position = vec3(aPos.x + offset, aPos.y, aPos.z);
    gl_Position = vec4(aPos, 1.0);// see how we directly give a vec3 to vec4's constructor
    testPosition = aPos;
}