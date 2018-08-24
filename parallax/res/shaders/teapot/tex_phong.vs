#version 430

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TexCoords;

uniform mat4 MVP;
uniform mat3 normalMat;
uniform mat4 modelMat;

void main() {
  v_TexCoords = vTexCoords;
  v_Normal = vec3(normalize(normalMat * vNormal));
  v_Position = vec3(modelMat * vec4(vPos, 1.0));
  gl_Position = MVP * vec4(vPos, 1.0);
}
