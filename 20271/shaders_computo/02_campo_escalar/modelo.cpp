// modelo.cpp
#include "modelo.h"

Modelo crearModelo(int ancho, int alto) {
    Modelo m;
    m.ancho = ancho;
    m.alto  = alto;

    // --- Textura que el compute shader escribirá como "imagen" ---
    glGenTextures(1, &m.textura);
    glBindTexture(GL_TEXTURE_2D, m.textura);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, ancho, alto, 0, GL_RED, GL_FLOAT, nullptr);
    // Sin mipmaps: el filtro de minificación NO puede ser *_MIPMAP_* (textura incompleta)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // --- Rectángulo [-1,1] x [-1,1] dibujado como GL_TRIANGLE_STRIP ---
    float vertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
    };
    glGenVertexArrays(1, &m.vao);
    glBindVertexArray(m.vao);
    glGenBuffers(1, &m.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    return m;
}

void dibujarModelo(const Modelo& m) {
    glBindVertexArray(m.vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void destruirModelo(Modelo& m) {
    glDeleteTextures(1, &m.textura);
    glDeleteBuffers(1, &m.vbo);
    glDeleteVertexArrays(1, &m.vao);
}
