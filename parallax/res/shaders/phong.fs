#version 430 core

#define NR_POINT_LIGHTS 1

struct SpotLight {
	
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct PointLight {
	
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

struct DirLight {
	vec3 direction;
	
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
in vec3 v_Normal;
in vec3 v_FragPos;

out vec4 out_FragColor;

uniform vec3 u_cameraDirection;
uniform vec3 u_cameraPosition;

uniform Material u_material;
uniform DirLight u_dirLight;
uniform SpotLight u_spotLight;
uniform PointLight u_pointLights[NR_POINT_LIGHTS];

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(u_cameraPosition - fragPos);
	float theta = dot(lightDir, normalize(-u_cameraDirection));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);

	vec3 ambient 	= light.ambient * vec3(texture(u_material.texture_diffuse1, v_TexCoords));
	vec3 diffuse 	= light.diffuse * diff * vec3(texture(u_material.texture_diffuse1, v_TexCoords));
	vec3 specular	= light.specular * spec * vec3(texture(u_material.texture_specular1, v_TexCoords));

	float distance 		= length(u_cameraPosition - fragPos);
	float attenuation 	= 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	diffuse *= intensity * attenuation;
	specular *= intensity * attenuation;

	return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	float distance 		= length(light.position - fragPos);
	float attenuation 	= 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);

	vec3 ambient 	= light.ambient * vec3(texture(u_material.texture_diffuse1, v_TexCoords));
	vec3 diffuse 	= light.diffuse * diff * vec3(texture(u_material.texture_diffuse1, v_TexCoords));
	vec3 specular	= light.specular * spec * vec3(texture(u_material.texture_specular1, v_TexCoords));

	//ambient *= attenuation;
	//diffuse *= attenuation;
	//specular *= attenuation;


	return (ambient + diffuse + specular);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),u_material.shininess);

	vec3 ambient 	= light.ambient 	* vec3(texture(u_material.texture_diffuse1, v_TexCoords));
	vec3 diffuse 	= light.diffuse 	* diff 	* vec3(texture(u_material.texture_diffuse1, v_TexCoords));
	vec3 specular	= light.specular 	* spec 	* vec3(texture(u_material.texture_specular1, v_TexCoords));

	return (ambient + diffuse + specular);
}

void main() {
	vec3 norm 		= normalize(v_Normal);
	vec3 viewDir 	= normalize(u_cameraPosition - v_FragPos);

	//vec3 result = calcDirLight(u_dirLight, norm, viewDir);
	vec3 result;
	//for(int i = 0; i < NR_POINT_LIGHTS; ++i) {
		result += calcPointLight(u_pointLights[0], norm, v_FragPos, viewDir);
	//}
	//result +=calcSpotLight(u_spotLight, norm, v_FragPos, viewDir);
	out_FragColor = vec4(result, 1.0);

}
