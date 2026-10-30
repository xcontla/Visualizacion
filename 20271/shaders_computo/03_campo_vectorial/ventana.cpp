// ventana.cpp
#include "ventana.h"
#include <cstdio>
#include <cstdlib>

static void errorGLFW(int codigo, const char* descripcion) {
    fprintf(stderr, "Error GLFW %d: %s\n", codigo, descripcion);
}

// ESC cierra la ventana
static void teclado(GLFWwindow* ventana, int tecla, int, int accion, int) {
    if (tecla == GLFW_KEY_ESCAPE && accion == GLFW_PRESS)
        glfwSetWindowShouldClose(ventana, GLFW_TRUE);
}

GLFWwindow* crearVentana(int ancho, int alto, const char* titulo, bool visible) {
    glfwSetErrorCallback(errorGLFW);
#ifdef GLFW_PLATFORM_X11
    // GLFW >= 3.4 en Linux: forzamos X11 porque GLEW (GLX) falla en Wayland puro
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif
    if (!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, visible ? GLFW_TRUE : GLFW_FALSE);

    GLFWwindow* ventana = glfwCreateWindow(ancho, alto, titulo, nullptr, nullptr);
    if (!ventana) {
        fprintf(stderr, "No se pudo crear la ventana (se requiere OpenGL 4.3)\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(ventana);
    glfwSwapInterval(1);                     // sincronía vertical
    glfwSetKeyCallback(ventana, teclado);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "No se pudo inicializar GLEW\n");
        exit(EXIT_FAILURE);
    }
    glGetError();  // GLEW a veces deja un error "falso"; lo limpiamos

    printf("OpenGL %s\nGPU: %s\n", glGetString(GL_VERSION), glGetString(GL_RENDERER));
    return ventana;
}

void destruirVentana(GLFWwindow* ventana) {
    glfwDestroyWindow(ventana);
    glfwTerminate();
}
