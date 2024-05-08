#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec4 a_color;

out vec4 f_color;


void main()
{
	f_color = a_color;
	gl_Position = vec4(aPos, 0.f, 1.0);
}