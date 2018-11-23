R"(
#version 330 core

layout(location = 0) out vec4 out_Color
// TODO: 2-channel position output
layout(location = 1) out vec4 out_Position;

in vec4  v_Color;
in vec3  v_Position;
in vec2  v_UV;
in float v_TexID;

uniform sampler2D sys_Textures[32];

void main() {
	vec4 texColor = v_Color;
// TODO: get rid of if
	if (v_TexID > 0.0 {
		int texID = int(v_TexID - 0.5);
		texColor *= texture(sys_Textures[texID], v_UV);
	}
	// TEMPORARY SOLUTION
	if (texColor.a == 0.0f)
		discard;

	out_Color = texColor;
	out_Position = v_Position.xy;
	gl_FragDepth = v_Position.z;
}
)"
