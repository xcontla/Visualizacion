#pragma once
#include <vector>
#include "../header/shader.h"


class Renderable{

    public: 
        virtual void init() = 0;
        virtual void render(glm::mat4 view, glm::mat4 projection) = 0;
        virtual void update(float timeValue) = 0;
        virtual void finish() = 0;
        virtual ~Renderable() = default;

    protected:
        
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    Shader *shader;
    glm::mat4 model;
};