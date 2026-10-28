#version 430
layout(location = 0) in vec2 posicion;
out vec2 uv;

void main() {
    uv = posicion * 0.5 + 0.5;          // [-1,1] -> [0,1]
    gl_Position = vec4(posicion, 0.0, 1.0);
}
