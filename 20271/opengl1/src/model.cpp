#include "../header/model.h"
#include <cmath>
#include <iostream>

    Model::Model()
    {
/*
        vertices[0]  =-0.5f; vertices[1]  = -0.5f; vertices[2]  =  0.0f; vertices[3]  = 0.0f; vertices[4]  = 0.0f;// v0
        vertices[5]  = 0.5f; vertices[6]  = -0.5f; vertices[7]  =  0.0f; vertices[8]  = 0.5f; vertices[9]  = 0.0f;// v1
        vertices[10] = 0.5f; vertices[11] =  0.5f; vertices[12] =  0.0f; vertices[13] = 0.5f; vertices[14] = 1.0f;// v2
        vertices[15] =-0.5f; vertices[16] =  0.5f; vertices[17] =  0.0f; vertices[18] = 0.0f; vertices[19] = 1.0f;// v3
        vertices[20] = 1.5f; vertices[21] = -0.5f; vertices[22] =  0.0f; vertices[23] = 1.0f; vertices[24] = 0.0f;// v4
        vertices[25] = 1.5f; vertices[26] =  0.5f; vertices[27] =  0.0f; vertices[28] = 1.0f; vertices[29] = 1.0f;// v5
        vertices[30] = -1.5f; vertices[31] = -0.5f; vertices[32] =  0.0f; vertices[33] = 1.0f; vertices[34] = 0.0f;// v6
        vertices[35] = -1.5f; vertices[36] =  0.5f; vertices[37] =  0.0f; vertices[38] = 1.0f; vertices[39] = 1.0f;// v7

        
        indices[0] = 0;indices[1] = 1;indices[2] = 2;
        indices[3] = 2;indices[4] = 3;indices[5] = 0; // Cara 1
        
        indices[6] = 1;indices[7] = 4;indices[8] = 5;
        indices[9] = 1;indices[10] = 5;indices[11] = 2; // Cara 2

        
        indices[12] = 6;indices[13] = 0;indices[14] = 3;
        indices[15] = 6;indices[16] = 3;indices[17] = 7; // Cara 3
    
    */
        }

    Model::Model(GLuint ancho, GLuint alto)
    {
        // reserve() solo aparta memoria; el tamaño sigue en 0 y push_back llena desde el inicio.
        // La malla tiene (ancho+1) x (alto+1) vértices.
        vertices.clear();
        indices.clear();
        vertices.reserve((ancho + 1) * (alto + 1) * 5);
        indices.reserve((ancho + 1) * (alto + 1));


        GLfloat x,y,z,u,v;
        GLfloat min_x = -2.0f, max_x = 2.0f, 
                min_z = -2.0f, max_z = 2.0f;

        GLuint index = 0; 
        for(GLuint i = 0; i < ancho + 1; i++){
            for(GLuint j = 0; j < alto + 1; j++){

                GLfloat delta_x = (max_x - min_x) / (GLfloat)ancho;
                GLfloat delta_z = (max_z - min_z) / (GLfloat)alto;
                
                x = min_x + i * delta_x;
                vertices.push_back(x);

                y = 0.0;
                vertices.push_back(y);

                z = min_z + j * delta_z;
                vertices.push_back(z);

                u = 0.0;
                vertices.push_back(u);
                v = 0.0;
                vertices.push_back(v);
                
                indices.push_back(index);

                index = index + 1;

                std::cout << "(" << x << "," << y << "," << z <<") - v" << index << std::endl;
            }
        }


        std::cout << vertices.size() << " - " << indices.size() << std::endl;
    }


    void Model::initModel()
    {

    modelmat = glm::mat4(1.0f);
    shader = new Shader("./shader/shader.vert","./shader/shader.frag");
         // Crear y enlazar el VAO y VBO
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*  vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Especificar el layout del vertex shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    }

    void Model::updateModel(float timeValue){
        angle = timeValue * glm::radians(5.0f); // 0.5 grados por segundo
        modelmat =  glm::rotate(glm::mat4(1.0f), 0.0f ,glm::vec3(0.0,0.0,1.0f)); ;
    }

    void Model::renderModel(glm::mat4 view, glm::mat4 projection){
        
        shader->use();

        // Enviar las matrices al shader
        shader->setMat4x4("model", modelmat);
        shader->setMat4x4("view", view);
        shader->setMat4x4("projection", projection);
        
        // Dibujar el cubo
        glBindVertexArray(VAO);
        glPointSize(4.0f);
        glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, 0);

    }
    void Model::finish(){

        
        shader->terminate();
        delete(shader);
        


        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }