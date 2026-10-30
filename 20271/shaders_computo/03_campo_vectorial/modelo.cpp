// modelo.cpp
#include "modelo.h"
#include <glm/glm.hpp>

Modelo crearModelo(int ancho, int alto, int nx, int ny) {
    Modelo m;
    m.ancho = ancho;  m.alto = alto;
    m.nx = nx;        m.ny = ny;

    // --- Textura del campo escalar ---
    glGenTextures(1, &m.textura);
    glBindTexture(GL_TEXTURE_2D, m.textura);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, ancho, alto, 0, GL_RED, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // --- Rectángulo de fondo ---
    float vertices[] = { -1, -1,   1, -1,   -1, 1,   1, 1 };
    glGenVertexArrays(1, &m.vaoFondo);
    glBindVertexArray(m.vaoFondo);
    glGenBuffers(1, &m.vboFondo);
    glBindBuffer(GL_ARRAY_BUFFER, m.vboFondo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // --- Buffer de flechas: vec4 por vértice (x, y, magnitud, 1) ---
    GLsizeiptr bytes = (GLsizeiptr)nx * ny * 6 * sizeof(glm::vec4);
    glGenBuffers(1, &m.flechas);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m.flechas);
    glBufferData(GL_SHADER_STORAGE_BUFFER, bytes, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m.flechas);   // binding = 1 en gradiente.comp

    // El MISMO buffer usado como atributo de vértices: sin copiar nada a la CPU
    glGenVertexArrays(1, &m.vaoFlechas);
    glBindVertexArray(m.vaoFlechas);
    glBindBuffer(GL_ARRAY_BUFFER, m.flechas);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    return m;
}

void dibujarFondo(const Modelo& m) {
    glBindVertexArray(m.vaoFondo);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void dibujarFlechas(const Modelo& m) {
    glBindVertexArray(m.vaoFlechas);
    glDrawArrays(GL_LINES, 0, m.nx * m.ny * 6);
}

void destruirModelo(Modelo& m) {
    glDeleteTextures(1, &m.textura);
    glDeleteBuffers(1, &m.vboFondo);
    glDeleteBuffers(1, &m.flechas);
    glDeleteVertexArrays(1, &m.vaoFondo);
    glDeleteVertexArrays(1, &m.vaoFlechas);
}
