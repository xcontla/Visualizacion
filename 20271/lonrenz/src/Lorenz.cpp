#include "../header/Lorenz.h"
#include <cmath>
#include <iostream>

Lorenz::Lorenz(){

}

Lorenz::Lorenz(GLfloat s, GLfloat r, GLfloat b, GLuint tam){
    

    index = 0;
    sigma = s; beta = b; rho = r;
    GLfloat dt = 0.01f;
    x = -1.0f,y = 0.0f, z = 10.0f, u = 0.0f, v = 0.0f;

        GLfloat dx = sigma * (y - x) * dt;
        x += dx;
        vertices.push_back(x);
        GLfloat dy = ((x * (rho - z)) - y) * dt ;
        y += dy;
        vertices.push_back(y);
        GLfloat dz = (x * y - beta * z ) * dt;
        z += dz;
        vertices.push_back(z);
        u = 0.0;
        vertices.push_back(u);
        v = 0.0;
        vertices.push_back(v);

        indices.push_back(index);

        std::cout << x << "," << y << "," << z << std::endl;


    std::cout << vertices.size() << " - " << indices.size() << std::endl;

}


    void Lorenz::init()
    {

    model = glm::mat4(1.0f);
    shader = new Shader("./shader/shader.vert","./shader/shader.frag");
         // Crear y enlazar el VAO y VBO
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*  vertices.size(), &vertices[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STREAM_DRAW);

    // Especificar el layout del vertex shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    }

    void Lorenz::update(float deltatime){
        float dt = 0.01f;
        GLfloat dx = sigma * (y - x) * dt;
        x += dx;
        vertices.push_back(x);
        GLfloat dy = ((x * (rho - z)) - y) * dt ;
        y += dy;
        vertices.push_back(y);
        GLfloat dz = (x * y - beta * z ) * dt;
        z += dz;
        vertices.push_back(z);
        u = 0.0;
        vertices.push_back(u);
        v = 0.0;
        vertices.push_back(v);

        indices.push_back(index++);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*  vertices.size(), &vertices[0], GL_STREAM_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STREAM_DRAW);

        
        angle = deltatime * glm::radians(5.0f); // 0.5 grados por segundo
        model =  glm::rotate(glm::mat4(1.0f), 0.0f ,glm::vec3(0.0,1.0,0.0f)); ;
    }

    void Lorenz::render(glm::mat4 view, glm::mat4 projection){
        
        shader->use();

        // Enviar las matrices al shader
        shader->setMat4x4("model", model);
        shader->setMat4x4("view", view);
        shader->setMat4x4("projection", projection);
        
        // Dibujar el cubo
        glBindVertexArray(VAO);
        glPointSize(2.0f);
        glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, 0);

    }
    void Lorenz::finish(){

        
    std::cout << "Finish Lorenz" << std::endl;
        
        shader->terminate();
        delete(shader);
        


        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }