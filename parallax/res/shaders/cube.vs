#version 430 core

layout (location = 0) in vec3 a_FragPos;
layout(early_fragment_tests) in;

out vec3 v_TexCoords;

uniform mat4 u_MVP;

void main()
{
    v_TexCoords = a_FragPos;
    gl_Position 	= (u_MVP * vec4(a_FragPos, 1.0)).xyww;
}
