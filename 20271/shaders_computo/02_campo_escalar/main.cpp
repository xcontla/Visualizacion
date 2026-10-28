// main.cpp — Ejemplo 2: visualización de un campo escalar
// El compute shader CALCULA el campo en una textura y el fragment shader lo COLOREA.
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ventana.h"
#include "modelo.h"
#include "shader.h"

const int TAM   = 512;  // resolución del campo
const int GRUPO = 16;   // debe coincidir con local_size_x/y del shader

int main() {
    GLFWwindow* ventana = crearVentana(700, 700, "Ejemplo 2: campo escalar");

    Modelo modelo     = crearModelo(TAM, TAM);
    GLuint progCampo  = crearShaderComputo("shaders/campo.comp");
    GLuint progRender = crearShaderRender("shaders/quad.vert", "shaders/escalar.frag");

    // La textura se conecta a la unidad de IMAGEN 0 (para imageStore en el compute shader)
    glBindImageTexture(0, modelo.textura, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

    // Uniforms que no cambian
    glUseProgram(progRender);
    glUniform1i(glGetUniformLocation(progRender, "campo"), 0);   // unidad de TEXTURA 0
    glUniform1f(glGetUniformLocation(progRender, "minimo"), -1.3f);
    glUniform1f(glGetUniformLocation(progRender, "maximo"),  1.3f);
    glUniform1f(glGetUniformLocation(progRender, "numIsolineas"), 12.0f);

    while (!glfwWindowShouldClose(ventana)) {
        float t = (float)glfwGetTime();

        // --- 1) Cómputo: calcular el campo ---
        glm::vec2 c1 = 0.5f * glm::vec2(std::cos(t), std::sin(t));  // gira en círculo
        glm::vec2 c2 = -c1;

        glUseProgram(progCampo);
        glUniform2fv(glGetUniformLocation(progCampo, "centro1"), 1, glm::value_ptr(c1));
        glUniform2fv(glGetUniformLocation(progCampo, "centro2"), 1, glm::value_ptr(c2));
        glUniform1f (glGetUniformLocation(progCampo, "tiempo"), t);
        glDispatchCompute((TAM + GRUPO - 1) / GRUPO, (TAM + GRUPO - 1) / GRUPO, 1);

        // Barrera: lo escrito con imageStore debe estar listo antes de leerlo con texture()
        glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT);

        // --- 2) Dibujo: mostrar el campo con mapa de color ---
        int ancho, alto;
        glfwGetFramebufferSize(ventana, &ancho, &alto);
        glViewport(0, 0, ancho, alto);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(progRender);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, modelo.textura);
        dibujarModelo(modelo);

        glfwSwapBuffers(ventana);
        glfwPollEvents();
    }

    glDeleteProgram(progCampo);
    glDeleteProgram(progRender);
    destruirModelo(modelo);
    destruirVentana(ventana);
    return 0;
}
