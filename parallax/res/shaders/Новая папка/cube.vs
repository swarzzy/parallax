#version 430 core

layout (location = 0) in vec3 a_FragPos;

uniform mat4 u_MVP;

void main()
{
    gl_Position 	= u_MVP * vec4(a_FragPos, 1.0);
}
