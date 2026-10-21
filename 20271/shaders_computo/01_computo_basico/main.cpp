// main.cpp — Ejemplo 1: compute shader básico
// Calcula b[i] = escala * a[i]^2 en la GPU y lee el resultado en la CPU.
#include <cstdio>
#include <cmath>
#include "ventana.h"
#include "modelo.h"
#include "shader.h"

const int N         = 1000;  // a propósito NO es múltiplo de 64
const int TAM_GRUPO = 64;    // debe coincidir con local_size_x del shader

int main() {
    // Necesitamos un contexto OpenGL, aunque no dibujemos nada: ventana oculta
    GLFWwindow* ventana = crearVentana(200, 200, "Ejemplo 1", false);

    // Límites del hardware
    GLint maxGrupos, maxTam, maxInvocaciones;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &maxGrupos);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE,  0, &maxTam);
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &maxInvocaciones);
    printf("\nMax. grupos en x: %d | max. hilos por grupo en x: %d | max. hilos por grupo: %d\n\n",
           maxGrupos, maxTam, maxInvocaciones);

    Modelo modelo   = crearModelo(N);
    GLuint programa = crearShaderComputo("shaders/cuadrado.comp");

    // 1) Activar el programa y mandar uniforms
    glUseProgram(programa);
    glUniform1f (glGetUniformLocation(programa, "escala"), 0.5f);
    glUniform1ui(glGetUniformLocation(programa, "n"), N);

    // 2) Lanzar: ceil(N / 64) grupos
    int grupos = (N + TAM_GRUPO - 1) / TAM_GRUPO;
    printf("Lanzando %d grupos x %d hilos = %d hilos para %d datos\n\n",
           grupos, TAM_GRUPO, grupos * TAM_GRUPO, N);
    glDispatchCompute(grupos, 1, 1);

    // 3) Barrera: esperar a que el shader termine de escribir antes de leer el buffer
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);

    // 4) Leer resultados
    std::vector<float> salida;
    std::vector<glm::uvec4> info;
    leerResultados(modelo, salida, info);

    printf("   i |       b[i] | global | local | grupo\n");
    printf("-----+------------+--------+-------+------\n");
    int muestra[] = {0, 1, 2, 63, 64, 65, 127, 128, 998, 999};
    for (int i : muestra)
        printf("%4d | %10.1f | %6u | %5u | %5u\n", i, salida[i], info[i].x, info[i].y, info[i].z);

    // Verificación contra la CPU
    int errores = 0;
    for (int i = 0; i < N; i++) {
        float esperado = 0.5f * i * i;
        if (std::fabs(salida[i] - esperado) > 1e-4f * (esperado + 1.0f)) errores++;
    }
    printf("\nVerificacion: %s (%d errores)\n", errores == 0 ? "correcto" : "INCORRECTO", errores);

    glDeleteProgram(programa);
    destruirModelo(modelo);
    destruirVentana(ventana);
    return 0;
}
