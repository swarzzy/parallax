#version 430
in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoords;

out vec4 out_Color;

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	float shininess;
};
struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 u_camPos;

uniform Material u_material;
uniform PointLight u_light;

vec3 phong() {
  vec3 s = normalize(u_light.position - v_Position);
  vec3 v = normalize(u_camPos - v_Position);
  vec3 diffColor = vec3(texture(u_material.texture_diffuse1, v_TexCoords));
  return	(u_light.ambient * diffColor) +
            (u_light.diffuse * max(dot(v_Normal, s), 0.0) * diffColor) +
            (u_light.specular * vec3(texture(u_material.texture_specular1, v_TexCoords)) *  //half-way vec approx
            	pow(max(dot(normalize(v + s), v_Normal), 0.0), u_material.shininess));

}

void main() {
  out_Color = vec4(phong(), 1.0);
}
