#version 430
in  vec2 uv;
out vec4 colorFinal;

uniform sampler2D campo;     // la misma textura, ahora leída con filtrado
uniform float minimo;
uniform float maximo;
uniform float numIsolineas;

// Mapa de color divergente: azul (bajo) - blanco (medio) - rojo (alto)
vec3 mapaColor(float t) {
    vec3 azul   = vec3(0.23, 0.30, 0.75);
    vec3 blanco = vec3(0.87, 0.87, 0.87);
    vec3 rojo   = vec3(0.71, 0.02, 0.15);
    return t < 0.5 ? mix(azul, blanco, t * 2.0) : mix(blanco, rojo, (t - 0.5) * 2.0);
}

void main() {
    float f = texture(campo, uv).r;
    float t = clamp((f - minimo) / (maximo - minimo), 0.0, 1.0);   // normalizar a [0,1]

    vec3 color = mapaColor(t);

    // Isolíneas: líneas donde t * numIsolineas es entero.
    // fwidth() mide cuánto cambia k entre píxeles vecinos -> grosor constante en pantalla.
    float k     = t * numIsolineas;
    float dist  = abs(fract(k - 0.5) - 0.5) / fwidth(k);
    float linea = 1.0 - min(dist, 1.0);
    color = mix(color, vec3(0.0), 0.6 * linea);

    colorFinal = vec4(color, 1.0);
}
