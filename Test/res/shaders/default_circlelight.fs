#version 430 core

out vec4 color;

in vec4 v_color;
in vec2 v_position;
in vec2 v_UV;
in float v_texID;

uniform vec2 u_lightPos;
uniform sampler2D u_textures[32];

void main() {
	vec4 texColor = v_color;
	if (v_texID > 0.0) {
		int texID = int(v_texID - 0.5);
		texColor *= texture(u_textures[texID], v_UV);
	}
	if (length(v_position - u_lightPos) < 100.0)
	color = texColor;
	else 
	color = vec4(0.0);
}