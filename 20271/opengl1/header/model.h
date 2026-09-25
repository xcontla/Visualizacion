#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../header/shader.h"
#include <vector>

class Model{
public:

    Shader* shader;
    //GLfloat vertices[40];
    //GLuint indices[18];
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    float angle;
    glm::mat4 modelmat;
    GLuint VAO, VBO, EBO;

    Model();
    //Model(GLfloat* vertices, GLuint indices);
    Model(GLuint ancho, GLuint largo); // plano

    void initModel();
    void renderModel(glm::mat4 view, glm::mat4 projection);
    void updateModel(float timeValue);
    void finish();


};