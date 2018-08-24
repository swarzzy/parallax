#version 430 core

layout (location = 0) in vec3 a_FragPos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoords;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_MVP;
uniform mat4 u_ModelViewMatrix;
uniform mat3 u_NormalMatrix;

void main()
{
    v_TexCoords		= a_TexCoords;
	v_Normal 		= normalize(u_NormalMatrix * a_Normal);
	v_FragPos 		= (u_ModelViewMatrix * vec4(a_FragPos, 1.0)).xyz;
    gl_Position 	= u_MVP * vec4(a_FragPos, 1.0);
}
