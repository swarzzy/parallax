R"(
#version 330 core

layout(location = 0) in vec2 a_Coords;

uniform mat4 sys_ProjectionMatrix = mat4(1.0f);

out V_OUT { 
	mat4 projectionMatrix;
} v_out;

void main() {
	gl_Position = sys_ProjectionMatrix * vec4(a_Coords, 0.0f, 1.0f);
	v_out.projectionMatrix = sys_ProjectionMatrix;
}
)"