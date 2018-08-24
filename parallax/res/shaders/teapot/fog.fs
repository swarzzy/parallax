#version 430

layout(early_fragment_tests) in;

struct FogInfo {
	float maxDist;
	float minDist;
	vec3 color;
};

in vec3 v_Position;
in vec3 v_Normal;

uniform FogInfo u_FogInfo;

uniform vec3 u_LightPosition;
uniform vec3 u_LightIntensivity;

uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;
uniform float u_shininess;

out vec4 out_Color;

vec3 phong() {
  vec3 position = normalize(v_Position);
  vec3 s = normalize(u_LightPosition - position);
  return u_LightIntensivity *
            (u_ambient +
              (u_diffuse * max(dot(s, v_Normal), 0.0)) +
              (u_specular *   //half-way vec approx
                  pow(max(dot(normalize(-position + s), v_Normal), 0.0), u_shininess)));
}

void main() {
  float dist = length(v_Position);
  float fogFactor = (u_FogInfo.maxDist - dist) /
  						 (u_FogInfo.maxDist - u_FogInfo.minDist);
  fogFactor = clamp(fogFactor, 0.0, 1.0);
  vec3 shadeColor = phong();
  vec3 color = mix(u_FogInfo.color, shadeColor, fogFactor);
  out_Color = vec4(color, 1.0);
}
