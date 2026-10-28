// modelo.h — Los datos: una textura con el campo escalar y un rectángulo para mostrarla
#pragma once
#include <GL/glew.h>

struct Modelo {
    int ancho, alto;  // resolución del campo escalar
    GLuint textura;   // campo escalar f(x,y), un float por texel (GL_R32F)
    GLuint vao, vbo;  // rectángulo que cubre toda la ventana
};

Modelo crearModelo(int ancho, int alto);
void dibujarModelo(const Modelo& m);
void destruirModelo(Modelo& m);
