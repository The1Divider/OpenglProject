#version 330 core

out vec4 FragColor;
in vec3 inColor;

void main()
{
    FragColor = vec4(inColor.x, inColor.y, inColor.z, 1.0);
}