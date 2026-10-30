// modelo.h — Igual que el ejemplo 2 + un buffer con las flechas del campo vectorial
#pragma once
#include <GL/glew.h>

struct Modelo {
    // Campo escalar (igual que el ejemplo 2)
    int ancho, alto;
    GLuint textura;
    GLuint vaoFondo, vboFondo;

    // Campo vectorial: nx * ny flechas, cada una con 6 vértices (3 líneas)
    int nx, ny;
    GLuint flechas;     // lo ESCRIBE el compute shader (SSBO) y lo LEE el vertex shader (VBO)
    GLuint vaoFlechas;
};

Modelo crearModelo(int ancho, int alto, int nx, int ny);
void dibujarFondo(const Modelo& m);
void dibujarFlechas(const Modelo& m);
void destruirModelo(Modelo& m);
