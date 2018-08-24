#version 430 core

struct DirLight {
	vec3 direction; // normalized
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material {
	sampler2D texture_diffuse0;
	sampler2D texture_specular0;
	sampler2D texture_normal0;
	
	float shininess;
};

in vec2 v_TexCoords;
in vec3 v_Normal; 	// normalized
in vec3 v_CamToFrag;
in vec3 v_Tangent;

out vec4 out_FragColor;

uniform Material u_Material;
uniform DirLight u_DirLight;

vec3 calcBumpedNormal() {

	vec3 tangent = normalize(v_Tangent - dot(v_Tangent, v_Normal) * v_Normal);
	vec3 bitangent = cross(tangent, v_Normal);
	vec3 bumpMapNormal = texture(u_Material.texture_normal0, v_TexCoords).xyz;
	bumpMapNormal = 2.0 * bumpMapNormal - vec3(1.0, 1.0, 1.0);
	vec3 newNormal;
	mat3 TBN = mat3(tangent, bitangent, v_Normal);
	newNormal = normalize(TBN * bumpMapNormal);
	return newNormal;
}

vec3 calcDirLight(vec3 normal) {
	float sDotN = max(dot(normal, -u_DirLight.direction), 0.0);
	vec3 spec = vec3(0.0);
	if (sDotN > 0.0)
		spec = u_DirLight.specular * pow(max(dot(normalize(v_CamToFrag - u_DirLight.direction), normal), 0.0), u_Material.shininess);
	vec3 diffTexColor = vec3(texture(u_Material.texture_diffuse0, v_TexCoords));
	return		(u_DirLight.ambient * diffTexColor) +
				(u_DirLight.diffuse * sDotN * diffTexColor) + 
				(spec * vec3(texture(u_Material.texture_specular0, v_TexCoords)));
}

void main() {
	vec3 normal = calcBumpedNormal();
	out_FragColor = vec4(calcDirLight(normal), 1.0);
	//out_FragColor = texture(u_Material.texture_normal0, v_TexCoords);

}
