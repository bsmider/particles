#shader vertex
#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 incolor;
out vec4 v_Color;

void main()
{
    v_Color = incolor;
    gl_Position = position;
};