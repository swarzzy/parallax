#version 430 core

layout (location = 0) in vec3 a_FragPos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec3 a_Tangent;
layout (location = 3) in vec2 a_TexCoords;


out vec3 v_Normal;
out vec3 v_Position;



uniform mat4 u_MVP;
uniform mat4 u_ModelMatrix;
uniform mat3 u_NormalMatrix;

void main()
{
    v_Normal = 		u_NormalMatrix * a_Normal;
	v_Position = 	(u_ModelMatrix * vec4(a_FragPos, 1.0)).xyz;
    gl_Position 	= u_MVP * vec4(a_FragPos, 1.0);
}
