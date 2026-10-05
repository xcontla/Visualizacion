#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../header/renderable.h"

class Ventana{
    public:
        GLuint width, height;
        GLFWwindow* window;
        glm::mat4 view, projection;

        Renderable * model;

        Ventana();
        Ventana(GLuint w, GLuint h);
        void initGLFW();
        void initGLEW();
        void initModels(Renderable* m);
        
        void initViewProyection();
        void render();
        void update();
        void idel();
        void finish();
};