#shader fragment
#version 460 core

in vec4 v_Color;
out vec4 FragColor;

void main()
{
   FragColor = v_Color;
   // FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
};