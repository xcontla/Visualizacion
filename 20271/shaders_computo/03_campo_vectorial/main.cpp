// main.cpp — Ejemplo 3: campo vectorial (gradiente del campo escalar del ejemplo 2)
// Pasada 1 (cómputo): campo escalar f(x,y) en una textura
// Pasada 2 (cómputo): gradiente de f -> vértices de flechas en un buffer
// Dibujo: fondo con mapa de color + flechas leídas DIRECTAMENTE del buffer
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ventana.h"
#include "modelo.h"
#include "shader.h"

const int TAM     = 512;  // resolución del campo escalar
const int FLECHAS = 32;   // flechas por lado
const int GRUPO   = 16;   // local_size_x/y de ambos compute shaders
const float MAG_MAX = 3.0f;

int grupos(int n) { return (n + GRUPO - 1) / GRUPO; }

int main() {
    GLFWwindow* ventana = crearVentana(700, 700, "Ejemplo 3: campo vectorial");

    Modelo modelo      = crearModelo(TAM, TAM, FLECHAS, FLECHAS);
    GLuint progCampo   = crearShaderComputo("shaders/campo.comp");
    GLuint progGrad    = crearShaderComputo("shaders/gradiente.comp");
    GLuint progFondo   = crearShaderRender("shaders/quad.vert",   "shaders/escalar.frag");
    GLuint progFlechas = crearShaderRender("shaders/flecha.vert", "shaders/flecha.frag");

    // READ_WRITE: un shader escribe la imagen y el otro la lee
    glBindImageTexture(0, modelo.textura, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32F);

    float largoMax = 0.9f * 2.0f / FLECHAS;   // 90% del tamaño de una celda

    glUseProgram(progGrad);
    glUniform2i(glGetUniformLocation(progGrad, "rejilla"), FLECHAS, FLECHAS);
    glUniform1f(glGetUniformLocation(progGrad, "escala"), largoMax / MAG_MAX);
    glUniform1f(glGetUniformLocation(progGrad, "largoMax"), largoMax);

    glUseProgram(progFondo);
    glUniform1i(glGetUniformLocation(progFondo, "campo"), 0);
    glUniform1f(glGetUniformLocation(progFondo, "minimo"), -1.3f);
    glUniform1f(glGetUniformLocation(progFondo, "maximo"),  1.3f);
    glUniform1f(glGetUniformLocation(progFondo, "numIsolineas"), 12.0f);
    glUniform1f(glGetUniformLocation(progFondo, "atenuacion"), 0.45f);

    glUseProgram(progFlechas);
    glUniform1f(glGetUniformLocation(progFlechas, "magMax"), MAG_MAX);

    while (!glfwWindowShouldClose(ventana)) {
        float t = (float)glfwGetTime();

        // --- Pasada 1: campo escalar (igual que el ejemplo 2) ---
        glm::vec2 c1 = 0.5f * glm::vec2(std::cos(t), std::sin(t));
        glm::vec2 c2 = -c1;
        glUseProgram(progCampo);
        glUniform2fv(glGetUniformLocation(progCampo, "centro1"), 1, glm::value_ptr(c1));
        glUniform2fv(glGetUniformLocation(progCampo, "centro2"), 1, glm::value_ptr(c2));
        glUniform1f (glGetUniformLocation(progCampo, "tiempo"), t);
        glDispatchCompute(grupos(TAM), grupos(TAM), 1);

        // La pasada 2 lee con imageLoad lo que la pasada 1 escribió con imageStore
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        // --- Pasada 2: gradiente -> flechas ---
        glUseProgram(progGrad);
        glDispatchCompute(grupos(FLECHAS), grupos(FLECHAS), 1);

        // El dibujo lee la textura (texture) y el buffer como vértices
        glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

        // --- Dibujo ---
        int ancho, alto;
        glfwGetFramebufferSize(ventana, &ancho, &alto);
        glViewport(0, 0, ancho, alto);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(progFondo);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, modelo.textura);
        dibujarFondo(modelo);

        glUseProgram(progFlechas);
        dibujarFlechas(modelo);

        glfwSwapBuffers(ventana);
        glfwPollEvents();
    }

    glDeleteProgram(progCampo);
    glDeleteProgram(progGrad);
    glDeleteProgram(progFondo);
    glDeleteProgram(progFlechas);
    destruirModelo(modelo);
    destruirVentana(ventana);
    return 0;
}
