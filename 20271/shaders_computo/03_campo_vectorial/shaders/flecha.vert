#version 430
layout(location = 0) in vec4 vertice;   // (x, y, magnitud, 1) escrito por gradiente.comp
out float magnitud;

void main() {
    magnitud    = vertice.z;
    gl_Position = vec4(vertice.xy, 0.0, 1.0);
}
