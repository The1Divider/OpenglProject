#version 460 core

in vec3 position;
in vec4 colour;

out vec4 outColour;

void main()
{
  gl_Position = vec4(position, 1.0);
  outColour = colour;
}