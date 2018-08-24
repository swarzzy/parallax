#version 430

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec3 v_Position;
out vec3 v_Normal;

uniform mat4 mvp;
uniform mat3 normalMat;
uniform mat4 modelViewMat;

void main() {
  v_Normal = normalize(normalMat * vNormal);
  v_Position = vec3(modelViewMat * vec4(vPos, 1.0));
  gl_Position = mvp * vec4(vPos, 1.0);
}
