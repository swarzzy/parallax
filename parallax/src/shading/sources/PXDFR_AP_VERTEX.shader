R"(
#version 330 core

layout(location = 0) in vec2   a_Coords;
layout(location = 1) in vec2   a_UV;

out vec2 v_UV;

void main() {
	v_UV = a_UV;
	gl_Position = vec4(a_Coords, 0.0f, 1.0f);
}
)"