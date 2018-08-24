#version 430

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;
uniform mat4 mvp;
void main() {
  gl_Position = mvp * vec4(vPos, 1.0);
}
