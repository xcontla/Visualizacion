// modelo.cpp
#include "modelo.h"

// Crea un SSBO y lo conecta al "binding" indicado (el mismo número que en el shader)
static GLuint crearSSBO(GLsizeiptr bytes, const void* datos, GLuint binding) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, bytes, datos, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, buffer);
    return buffer;
}

Modelo crearModelo(int n) {
    Modelo m;
    m.n = n;

    std::vector<float> datos(n);
    for (int i = 0; i < n; i++) datos[i] = (float)i;   // 0, 1, 2, ..., n-1

    m.entrada = crearSSBO(n * sizeof(float),      datos.data(), 0);
    m.salida  = crearSSBO(n * sizeof(float),      nullptr,      1);
    m.info    = crearSSBO(n * sizeof(glm::uvec4), nullptr,      2);
    return m;
}

// Copia los resultados de la GPU a la CPU
void leerResultados(const Modelo& m, std::vector<float>& salida, std::vector<glm::uvec4>& info) {
    salida.resize(m.n);
    info.resize(m.n);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m.salida);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, m.n * sizeof(float), salida.data());

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m.info);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, m.n * sizeof(glm::uvec4), info.data());
}

void destruirModelo(Modelo& m) {
    glDeleteBuffers(1, &m.entrada);
    glDeleteBuffers(1, &m.salida);
    glDeleteBuffers(1, &m.info);
}
