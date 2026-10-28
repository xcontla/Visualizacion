// ventana.h — Crear y destruir la ventana (GLFW) y el contexto OpenGL (GLEW)
#pragma once
#include <GL/glew.h>     // GLEW siempre antes que GLFW
#include <GLFW/glfw3.h>

// Crea una ventana con contexto OpenGL 4.3 core (mínimo para compute shaders).
// visible = false crea una ventana oculta: sirve cuando solo queremos el contexto.
GLFWwindow* crearVentana(int ancho, int alto, const char* titulo, bool visible = true);
void destruirVentana(GLFWwindow* ventana);
