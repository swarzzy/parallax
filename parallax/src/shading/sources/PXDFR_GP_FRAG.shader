R"(
#version 330 core

layout(location = 0) out vec3 out_Color;
layout(location = 1) out vec3 out_NormalColor;

in vec4  v_Color;
in float v_Depth;
in vec2  v_UV;
in float v_TexID;
in float v_NormalID;

uniform sampler2D sys_Textures[32];

void main() {
	vec4 texColor = v_Color;
	vec4 normalColor = vec4(0.5f, 0.5, 1.0, 1.0);
// TODO: get rid of if
	if (v_TexID > 0.0) {
		int texID = int(v_TexID - 0.5);
		texColor *= texture(sys_Textures[texID], v_UV);
		if (v_NormalID > 0.0) {
		int normalID = int(v_NormalID - 0.5);
		normalColor = texture(sys_Textures[normalID], v_UV);
		}
	}
	// TEMPORARY SOLUTION
	if (texColor.a == 0.0f)
		discard;

	out_Color = texColor.xyz;
	out_NormalColor = normalColor.xyz;
	gl_FragDepth = v_Depth;
}
)"
