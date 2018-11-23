R"(
#version 330 core

#define LIGHT_VOLUME_SEGMENTS_NR 12
#define MAX_LIGHTS_NR 30

struct Light {
	vec3 color;
	float radius;
	vec2 position;
	float intensity;
	float depth;
};

layout (std140) uniform ub_Lights {
	Light u_Lights[MAX_LIGHTS_NR];
};

uniform vec2 sys_ViewportSize;

uniform sampler2D sys_Texture;
uniform sampler2D sys_DepthTexture;

out vec4 out_Color;

void main() {
	vec2 UV = vec2(gl_FragCoord.x / sys_ViewportSize.x + 1, gl_FragCoord.y / sys_ViewportSize.y + 1);
	vec4 textureColor = texture(sys_Texture, UV);
	vec4 fragDepth = texture(sys_DepthTexture, UV);
	int primitiveID = gl_PrimitiveID / LIGHT_VOLUME_SEGMENTS_NR;
	float distance = length(u_Lights[primitiveID].position - gl_FragCoord.xy);
	//float attenuation = 1.0 / (u_Lights[primitiveID].constant, + 
	//						   u_Lights[primitiveID].linear * distance + 
	//						   u_Lights[primitiveID].quadratic * (distance * distance));

	float att = clamp(1.0 - distance / u_Lights[primitiveID].radius, 0.0, 1.0f);
	att *= att;

	float depthDiff = sign(u_Lights[primitiveID].depth - fragDepth.r);
	float isLightAboveFrag = step(0.0f, depthDiff);

	float intensity = u_Lights[primitiveID].intensity;
	out_Color = vec4(u_Lights[primitiveID].color, 1.0f) 
			  			* vec4(att, att, att, 1.0f) 
			  			* textureColor 
			  			* vec4(intensity, intensity, intensity, 1.0f)
			  			* vec4(isLightAboveFrag, isLightAboveFrag, isLightAboveFrag, 1.0f);
}
)"
