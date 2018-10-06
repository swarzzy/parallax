R"(
#version 430 core

layout(location = 0) in vec3 a_coord;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in float a_texID;
layout(location = 3) in vec4 a_color;

out vec4  v_color;
out vec2  v_position;
out vec2  v_UV;
out float v_texID;

uniform mat4 u_ProjectionMatrix = mat4(1.0);
uniform mat4 u_ModelMatrix = mat4(1.0);

void main() {
	v_color = a_color;
	v_UV = a_uv;
	v_position = (u_ModelMatrix * vec4(a_coord, 1.0)).xy;
	v_texID = a_texID;
	gl_Position = u_ProjectionMatrix * u_ModelMatrix * vec4(a_coord, 1.0);
}
)"