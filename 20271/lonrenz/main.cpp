#include "./header/ventana.h"
#include "./header/shader.h"
#include <iostream>
#include "./header/Lorenz.h"

Ventana *ventana;
Renderable *model;

void finish(){
    
    std::cout << "Finish Main" << std::endl;
    ventana->finish();
    glfwTerminate();
    delete(model);
    delete(ventana);
}

void init(){
    ventana = new Ventana(600,600);
    // Inicializar GLFW
    ventana->initGLFW();
    // Inicializar GLEW
    ventana->initGLEW();
    
    //model = new Model(100,100);
    model = new Lorenz(10.0f,28.0f,8.0f/3.0f, 5000);
    ventana->initModels(model);
    ventana->initViewProyection();

}

int main() {
    
    init();
    ventana->render();
    finish();

    return 0;
}
