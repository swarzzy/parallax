#version 430 core

layout (location = 0) in vec3 a_FragPos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec3 a_Tangent;
layout (location = 3) in vec2 a_TexCoords;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_CamToFrag;
out mat3 v_TBN;

uniform mat4 u_MVP;
uniform mat4 u_ModelMatrix;
uniform mat3 u_NormalMatrix;

uniform vec3 u_CameraPosition;

mat3 calcTBN(vec3 in_tangent, vec3 in_normal) {

	vec3 tangent = normalize(in_tangent - dot(in_tangent, in_normal) * in_normal);
	vec3 bitangent = cross(tangent, in_normal);
	return mat3(tangent, bitangent, in_normal);
}

void main()
{
    v_TexCoords		= a_TexCoords;
	v_Normal 		= normalize(u_NormalMatrix * a_Normal);
	v_TBN 			= calcTBN(normalize(u_NormalMatrix * a_Tangent), v_Normal);
	v_CamToFrag 	= normalize(u_CameraPosition - 
							(u_ModelMatrix * vec4(a_FragPos, 1.0f)).xyz);
    gl_Position 	= u_MVP * vec4(a_FragPos, 1.0);
}
