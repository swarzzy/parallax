#version 430 core

in vec3 v_TexCoords;

out vec4 out_FragColor;

uniform samplerCube skybox;

void main() {

	out_FragColor = texture(skybox, v_TexCoords);

}
