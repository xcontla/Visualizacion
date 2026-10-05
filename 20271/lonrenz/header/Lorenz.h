#pragma once

#include "./renderable.h"

class Lorenz: public Renderable{

    public:
    float angle, sigma, beta, rho, x,y,z,u,v;
    GLuint VAO, VBO, EBO, index;

    Lorenz();
    Lorenz(GLfloat s, GLfloat r, GLfloat b, GLuint tam);

    void init() override;
    void render(glm::mat4 view, glm::mat4 projection) override;
    void update(float timeValue) override;
    void finish() override;


};