// shader.h — Leer archivos de shaders, compilarlos y enlazarlos
#pragma once
#include <GL/glew.h>
#include <string>

std::string leerArchivo(const char* ruta);

// Programa con un solo compute shader
GLuint crearShaderComputo(const char* rutaComp);

// Programa clásico de dibujo: vertex + fragment
GLuint crearShaderRender(const char* rutaVert, const char* rutaFrag);
