R"(
#version 430 core

out vec4 color;

in vec4  v_color;
in vec2  v_position;
in vec2  v_UV;
in float v_texID;
in vec2  v_maskUV;

// Last texture is a mask
uniform sampler2D u_textures[32];

void main() {
	vec4 maskColor = texture(u_textures[31], v_maskUV);
	if (maskColor.r == 0.0f && maskColor.g == 0.0f && maskColor.b == 0.0f)
		discard;
	vec4 texColor = v_color;
	if (v_texID > 0.0) {
		int texID = int(v_texID - 0.5);
		texColor *= texture(u_textures[texID], v_UV);
	}
	color = texColor * maskColor;
}
)"
