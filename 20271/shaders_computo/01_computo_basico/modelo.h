// modelo.h — Los datos: tres buffers SSBO (Shader Storage Buffer Object)
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Modelo {
    int n;           // número de elementos
    GLuint entrada;  // binding = 0 : float a[]
    GLuint salida;   // binding = 1 : float b[]
    GLuint info;     // binding = 2 : uvec4 ids[] (para ver los índices de cada hilo)
};

Modelo crearModelo(int n);
void leerResultados(const Modelo& m, std::vector<float>& salida, std::vector<glm::uvec4>& info);
void destruirModelo(Modelo& m);
