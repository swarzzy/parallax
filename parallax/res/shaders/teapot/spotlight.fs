#version 430
in vec3 v_Position;
in vec3 v_Normal;

uniform vec3 u_LightPosition;
uniform vec3 u_LightIntensivity;

uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;
uniform float u_shininess;

uniform vec3 u_cameraPos;
uniform vec3 u_cameraFront;

out vec4 out_Color;

vec3 phong() {
  vec3 camPos = vec3(0.0, 0.0, 0.0);
  vec3 camDir = vec3(0.0, 0.0, 1.0);
  vec3 s = normalize(camPos - v_Position);
  float angle = dot(v_Position, camDir);
  float cutoff = cos(radians(12));
  if (angle < cutoff) {
  return u_LightIntensivity *
            (u_ambient +
              (u_diffuse * max(dot(s, v_Normal), 0.0)) +
              (u_specular *   //half-way vec approx
                  pow(max(dot(normalize(-v_Position + s), v_Normal), 0.0), u_shininess)));
} else
return u_ambient * u_LightIntensivity;
}

void main() {
  out_Color = vec4(phong(), 1.0);
}
