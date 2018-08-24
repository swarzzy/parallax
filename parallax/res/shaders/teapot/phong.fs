#version 430
in vec3 v_Position;
in vec3 v_Normal;

uniform vec3 u_LightPosition;
uniform vec3 u_LightIntensivity;

uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;
uniform float u_shininess;

out vec4 out_Color;

vec3 phong() {
  vec3 s = normalize(u_LightPosition - v_Position);
  return u_LightIntensivity *
            (u_ambient +
             (u_diffuse * max(dot(v_Normal, s), 0.0)) +
              (u_specular *   //half-way vec approx
                 pow(max(dot(normalize(-v_Position + s), v_Normal), 0.0), u_shininess)));

}

void main() {
  out_Color = vec4(phong(), 1.0);
}
