R"(
#version 330 core

uniform sampler2D sys_Texture;
uniform vec3 u_AmbientColor;
uniform float u_AmbientIntensity;

in vec2 v_UV;

out vec4 out_Color;

void main() {
	vec4 textureColor = texture(sys_Texture, v_UV);
	out_Color = vec4(textureColor.xyz * u_AmbientColor * vec3(u_AmbientIntensity, u_AmbientIntensity, u_AmbientIntensity), 1.0);
}
)"
