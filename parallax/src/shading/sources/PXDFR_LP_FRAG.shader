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

// TODO: System uniform buffer
uniform vec2 sys_ViewportSize;

uniform sampler2D sys_Texture;
uniform sampler2D sys_DepthTexture;
uniform sampler2D sys_NormalMap;

out vec4 out_Color;

in V_OUT {
	mat4 projectionMatrix;
	vec2 cameraPos;
} f_in;

void main() {
	vec2 UV = vec2(gl_FragCoord.x / sys_ViewportSize.x + 1, gl_FragCoord.y / sys_ViewportSize.y + 1);
	int primitiveID = gl_PrimitiveID / LIGHT_VOLUME_SEGMENTS_NR;
	
	vec4 albedo = texture(sys_Texture, UV);
	vec4 depth = texture(sys_DepthTexture, UV);
	vec3 normal = normalize(texture(sys_NormalMap, UV).xyz * 2.0 - 1.0);
	// NOTE: Why need to flip Y?
	normal  = vec3(normal.x, -normal.y, normal.z);
	
	// TODO: Get rig of projection matrix and matrix multiplications in frag shader
	vec3 lightPos = (f_in.projectionMatrix * vec4(u_Lights[primitiveID].position, 1.0, 1.0)).xyz;
	
	// Mapping frag coords from screenspace to NDC
	vec3 fragPosNDC;
	fragPosNDC.x = -1.0f + 2.0f / sys_ViewportSize.x * (gl_FragCoord.x);
	fragPosNDC.y = -1.0f + 2.0f / sys_ViewportSize.y * (gl_FragCoord.y);
	fragPosNDC.z = 0.0f;

	// Calculating toLight vector in NDC
	vec3 toLight = normalize(lightPos - fragPosNDC);

	float angle = max(dot(normal, toLight), 0.0f);

	// Calculating distance between light and frag in world space
	vec3 fragPosWorld = vec3(gl_FragCoord.x + f_in.cameraPos.x, gl_FragCoord.y + f_in.cameraPos.y, 0.0f);
	float distance = length(fragPosWorld - vec3(u_Lights[primitiveID].position, 1.0f));

	// Attenuation function
	float attenuation = clamp(1.0 - distance / (u_Lights[primitiveID].radius), 0.0, 1.0f);
	attenuation *= attenuation;

	// Checking is light above frag
	float depthDiff = sign(u_Lights[primitiveID].depth - depth.r);
	float isLightAboveFrag = step(0.0f, depthDiff);

	vec4 lightComponent = vec4(u_Lights[primitiveID].color 		// Light color
							 * u_Lights[primitiveID].intensity 	// Light intensity
							 * attenuation 						// Distance fading
							 * angle 							// Normal influence
							 * isLightAboveFrag,				// Checking is light above frag (0.0 if light is below frag)
							   1.0f);

	out_Color = albedo * lightComponent;
}
)"
