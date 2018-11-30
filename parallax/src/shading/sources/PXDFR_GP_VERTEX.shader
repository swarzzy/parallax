R"(
#version 330 core

layout(location = 0) in vec2   a_Coords;
layout(location = 1) in float  a_Depth;
layout(location = 2) in vec2   a_UV;
layout(location = 3) in float  a_TexID;
layout(location = 4) in float  a_NormalID;
layout(location = 5) in vec4   a_Color;

out vec4  v_Color;
out vec2  v_UV;
out float v_TexID;
out float v_NormalID;
out float v_Depth;

uniform mat4 sys_ProjectionMatrix;

void main() {
	v_Color = a_Color;
	v_UV = a_UV;
	v_TexID = a_TexID;
	v_NormalID = a_NormalID;
	gl_Position = sys_ProjectionMatrix * vec4(a_Coords, a_Depth, 1.0);
	v_Depth = gl_Position.z;
}
)"