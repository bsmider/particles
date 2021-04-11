#shader vertex
#version 460 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 incolor;
layout (location = 2) in vec2 aOffset;
out vec4 v_Color;

void main()
{
    v_Color = incolor;
    // gl_Position = position;
    gl_Position = vec4(position + aOffset, 0.0, 1.0);
};