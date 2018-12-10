R"(
#version 330 core

layout(location = 0) in vec2 a_Coords;

uniform mat4 sys_ProjectionMatrix = mat4(1.0f);

out V_OUT { 
	mat4 projectionMatrix;
	vec2 cameraPos;
} v_out;

void main() {
	// Calculatig camera position by decomposing projection matrix
	// Reference: https://lektiondestages.blogspot.com/2013/11/decompose-opengl-projection-matrix.html
	v_out.cameraPos = vec2( -(1 + sys_ProjectionMatrix[3][0]) / sys_ProjectionMatrix[0][0],
					        -(1 + sys_ProjectionMatrix[3][1]) / sys_ProjectionMatrix[1][1] );

	gl_Position = sys_ProjectionMatrix * vec4(a_Coords, 0.0f, 1.0f);
	v_out.projectionMatrix = sys_ProjectionMatrix;
}
)"