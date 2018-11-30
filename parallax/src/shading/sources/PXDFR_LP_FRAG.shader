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
uniform sampler2D sys_NormalMap;

out vec4 out_Color;

in mat4 proj;

void main() {
	vec2 UV = vec2(gl_FragCoord.x / sys_ViewportSize.x + 1, gl_FragCoord.y / sys_ViewportSize.y + 1);
	vec4 textureColor = texture(sys_Texture, UV);
	vec4 fragDepth = texture(sys_DepthTexture, UV);
	int primitiveID = gl_PrimitiveID / LIGHT_VOLUME_SEGMENTS_NR;

	vec3 lightPos = vec3(u_Lights[primitiveID].position, 1.0);
	vec3 fragPos = vec3(gl_FragCoord.x / sys_ViewportSize.x, gl_FragCoord.y / sys_ViewportSize.y,  0.0);

	vec3 toLight = normalize(normalize((proj * vec4(lightPos, 0.0)).xyz) - normalize((proj * vec4(fragPos, 0.0)).xyz));
	float distance = length(vec4(fragPos, 0.0) - vec4(lightPos, 0.0));

	vec3 normal = normalize(texture(sys_NormalMap, UV).xyz) * 2.0 - 1.0;
	normal  = vec3(normal.y, normal.x, normal.z);

	float angle = max(dot(normal, toLight), 0.0);

	//vec3 toLight = vec3(u_Lights[primitiveID].position, 1.0) - vec3(gl_FragCoord.xy, 0.0);
	//vec3 normal = normalize((texture(sys_NormalMap, UV).xyz * 2.0 - 1.0)).xyz;
	//normal = normal.xyz;
	//float angle = max(dot(normalize(toLight), normal), 0.0);
	//float attenuation = 1.0 / (u_Lights[primitiveID].constant, + 
	//						   u_Lights[primitiveID].linear * distance + 
	//						   u_Lights[primitiveID].quadratic * (distance * distance));

	float att = clamp(1.0 - distance / (u_Lights[primitiveID].radius) / 100, 0.0, 1.0f);
	att *= att;
	att *=  angle;
	//att = angle;

	float depthDiff = sign(u_Lights[primitiveID].depth - fragDepth.r);
	float isLightAboveFrag = step(0.0f, depthDiff);

	float intensity = u_Lights[primitiveID].intensity;
	out_Color = vec4(u_Lights[primitiveID].color, 1.0f) 
			  			* vec4(att, att, att, 1.0f) 
			  			* vec4(textureColor.r * angle, textureColor.g * angle, textureColor.b  *angle, 1.0)
			  			* vec4(intensity, intensity, intensity, 1.0f)
			  			* vec4(isLightAboveFrag, isLightAboveFrag, isLightAboveFrag, 1.0f);
	//out_Color = textureColor  * att;
}
)"
