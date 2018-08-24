#version 430 core

struct DirLight {
	vec3 direction; // normalized
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	
	float shininess;
};

in vec2 v_TexCoords;
in vec3 v_Normal; 	// normalized
in vec3 v_CamToFrag;

out vec4 out_FragColor;

uniform Material u_Material;
uniform DirLight u_DirLight;

vec3 calcDirLight() {
	float sDotN = max(dot(v_Normal, -u_DirLight.direction), 0.0);
	vec3 spec = vec3(0.0);
	if (sDotN > 0.0)
		spec = u_DirLight.specular * pow(max(dot(normalize(v_CamToFrag - u_DirLight.direction), v_Normal), 0.0), u_Material.shininess);
	vec3 diffTexColor = vec3(texture(u_Material.texture_diffuse1, v_TexCoords));
	return		(u_DirLight.ambient * diffTexColor) +
				(u_DirLight.diffuse * sDotN * diffTexColor) + 
				(spec * vec3(texture(u_Material.texture_specular1, v_TexCoords)));
}

void main() {
	
	out_FragColor = vec4(calcDirLight(), 1.0);
}
