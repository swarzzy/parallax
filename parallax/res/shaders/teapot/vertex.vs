#version 430

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec3 color;

struct LightInfo {
  vec4 positionMV;
  vec3 intensivity;
};

uniform LightInfo u_lights[2];

uniform vec3 u_diffuse;
uniform vec3 u_ambient;
uniform vec3 u_specular;
uniform float u_shininess;

uniform mat4 mvp;
uniform mat3 normalMat;
uniform mat4 modelViewMat;

vec3 phong(int i, vec3 position, vec3 norm) {
  vec4 t = u_lights[i].positionMV;
  vec3 s;
  if(t.w == 0.0)
         s = normalize(vec3(u_lights[i].positionMV));
  else
         s = normalize(vec3(u_lights[i].positionMV) - position);
  vec3 v = normalize(-position);
  vec3 r = reflect(-s, norm);
  return u_lights[i].intensivity * (u_ambient + (u_diffuse * max(dot(s, norm), 0.0)) +
            ( u_specular * pow(max(dot(r, v), 0.0), u_shininess)));
}

void main() {
  vec3 viewNorm = normalize( normalMat * vNormal);
  vec3 viewPos = vec3(modelViewMat * vec4(vPos, 1.0));
  color = vec3(0.0);
  for(int i = 0; i < 2; i++) {
    color += phong(i, viewPos, viewNorm);
  }
  gl_Position = mvp * vec4(vPos, 1.0);
}
