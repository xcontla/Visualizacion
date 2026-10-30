#version 430
in  float magnitud;
out vec4  colorFinal;

uniform float magMax;

void main() {
    // Magnitud codificada dos veces: longitud de la flecha y oscuridad del trazo
    float t = clamp(magnitud / magMax, 0.0, 1.0);
    colorFinal = vec4(mix(vec3(0.55), vec3(0.0), t), 1.0);
}
