#version 330 core

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
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 u_cameraDirection;
uniform vec3 u_cameraPosition;
uniform Material material;
uniform DirLight dirLight;
uniform SpotLight spotLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(u_cameraPosition - fragPos);
	float theta = dot(lightDir, normalize(-u_cameraDirection));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient 	= light.ambient * vec3(texture(material.texture_diffuse1, TexCoord));
	vec3 diffuse 	= light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoord));
	vec3 specular	= light.specular * spec * vec3(texture(material.texture_specular1, TexCoord));

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
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient 	= light.ambient * vec3(texture(material.texture_diffuse1, TexCoord));
	vec3 diffuse 	= light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoord));
	vec3 specular	= light.specular * spec * vec3(texture(material.texture_specular1, TexCoord));

	//ambient *= attenuation;
	//diffuse *= attenuation;
	//specular *= attenuation;


	return (ambient + diffuse + specular);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient 	= light.ambient 	* vec3(texture(material.texture_diffuse1, TexCoord));
	vec3 diffuse 	= light.diffuse 	* diff 	* vec3(texture(material.texture_diffuse1, TexCoord));
	vec3 specular	= light.specular 	* spec 	* vec3(texture(material.texture_specular1, TexCoord));

	return (ambient + diffuse + specular);
}

void main() {
	vec3 norm 		= normalize(Normal);
	vec3 viewDir 	= normalize(u_cameraPosition - FragPos);

	//vec3 result = calcDirLight(dirLight, norm, viewDir);
	vec3 result;
	//for(int i = 0; i < NR_POINT_LIGHTS; ++i) {
		result += calcPointLight(pointLights[0], norm, FragPos, viewDir);
	//}
	//result +=calcSpotLight(spotLight, norm, FragPos, viewDir);
	color = vec4(result, 1.0);

}