R"(
#version 330 core

layout(location = 0) in vec2   a_Coords;

uniform mat4 sys_ProjectionMatrix = mat4(1.0f);
out mat4 proj;

void main() {
	gl_Position = sys_ProjectionMatrix * vec4(a_Coords, 0.0f, 1.0f);
	proj = sys_ProjectionMatrix;
}
)"