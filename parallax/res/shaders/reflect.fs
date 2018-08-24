#version 430 core

in vec3 v_Normal;
in vec3 v_Position;

out vec4 out_FragColor;

uniform vec3 u_CameraPosition;
uniform samplerCube t_Skybox;


void main() {
	vec3 I = normalize(v_Position - u_CameraPosition);
	vec3 R = reflect(I, normalize(v_Normal));
	out_FragColor = vec4(texture(t_Skybox, R).rgb, 1.0);
}
