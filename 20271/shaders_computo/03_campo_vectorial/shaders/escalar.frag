#version 430
in  vec2 uv;
out vec4 colorFinal;

uniform sampler2D campo;
uniform float minimo;
uniform float maximo;
uniform float numIsolineas;
uniform float atenuacion;   // 0 = colores normales, 1 = blanco (para que resalten las flechas)

vec3 mapaColor(float t) {
    vec3 azul   = vec3(0.23, 0.30, 0.75);
    vec3 blanco = vec3(0.87, 0.87, 0.87);
    vec3 rojo   = vec3(0.71, 0.02, 0.15);
    return t < 0.5 ? mix(azul, blanco, t * 2.0) : mix(blanco, rojo, (t - 0.5) * 2.0);
}

void main() {
    float f = texture(campo, uv).r;
    float t = clamp((f - minimo) / (maximo - minimo), 0.0, 1.0);
    vec3 color = mapaColor(t);

    float k     = t * numIsolineas;
    float dist  = abs(fract(k - 0.5) - 0.5) / fwidth(k);
    color = mix(color, vec3(0.0), 0.4 * (1.0 - min(dist, 1.0)));

    colorFinal = vec4(mix(color, vec3(1.0), atenuacion), 1.0);
}
