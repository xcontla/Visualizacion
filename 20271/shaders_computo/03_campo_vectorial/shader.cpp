// shader.cpp
#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

std::string leerArchivo(const char* ruta) {
    std::ifstream archivo(ruta);
    if (!archivo) {
        std::cerr << "No se pudo abrir " << ruta << "\n";
        exit(EXIT_FAILURE);
    }
    std::stringstream contenido;
    contenido << archivo.rdbuf();
    return contenido.str();
}

static GLuint compilar(GLenum tipo, const char* ruta) {
    std::string codigo = leerArchivo(ruta);
    const char* fuente = codigo.c_str();

    GLuint shader = glCreateShader(tipo);
    glShaderSource(shader, 1, &fuente, nullptr);
    glCompileShader(shader);

    GLint ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[2048];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        std::cerr << "Error al compilar " << ruta << ":\n" << log << "\n";
        exit(EXIT_FAILURE);
    }
    return shader;
}

static void enlazar(GLuint programa) {
    glLinkProgram(programa);
    GLint ok;
    glGetProgramiv(programa, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[2048];
        glGetProgramInfoLog(programa, sizeof(log), nullptr, log);
        std::cerr << "Error al enlazar el programa:\n" << log << "\n";
        exit(EXIT_FAILURE);
    }
}

GLuint crearShaderComputo(const char* rutaComp) {
    GLuint cs = compilar(GL_COMPUTE_SHADER, rutaComp);
    GLuint programa = glCreateProgram();
    glAttachShader(programa, cs);
    enlazar(programa);
    glDeleteShader(cs);  // ya está dentro del programa
    return programa;
}

GLuint crearShaderRender(const char* rutaVert, const char* rutaFrag) {
    GLuint vs = compilar(GL_VERTEX_SHADER, rutaVert);
    GLuint fs = compilar(GL_FRAGMENT_SHADER, rutaFrag);
    GLuint programa = glCreateProgram();
    glAttachShader(programa, vs);
    glAttachShader(programa, fs);
    enlazar(programa);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return programa;
}
