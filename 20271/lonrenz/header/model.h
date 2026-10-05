#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderable.h"

class Model : public Renderable{
public:


    float angle;
    GLuint VAO, VBO, EBO;

    Model();
    Model(GLuint ancho, GLuint alto);
    //Model(GLfloat alfa, GLfloat beta, GLfloat ro);

    void init() override;
    void render(glm::mat4 view, glm::mat4 projection) override;
    void update(float timeValue) override;
    void finish() override;


};