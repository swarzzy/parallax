#version 430 core

layout (location = 0) in vec3 a_FragPos;
layout (location = 1) in vec3 a_Normal;
layout (location = 3) in vec2 a_TexCoords;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_CamToFrag;

uniform mat4 u_MVP;
uniform mat4 u_ModelMatrix;
uniform mat3 u_NormalMatrix;

uniform vec3 u_CameraPosition;

void main()
{
    v_TexCoords		= a_TexCoords;
	v_Normal 		= normalize(u_NormalMatrix * a_Normal);
	v_CamToFrag 	= normalize(u_CameraPosition - 
							(u_ModelMatrix * vec4(a_FragPos, 1.0f)).xyz);
    gl_Position 	= u_MVP * vec4(a_FragPos, 1.0);
}
