    #include "../header/model.h"
    #include <cmath>
    #include <iostream>

    Model::Model()
    {}

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
 
                z = min_z + j * delta_z;
                //y = exp( - x*x - z*z);
                y = 0.0;
                vertices.push_back(y);
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


    void Model::init()
    {

    model = glm::mat4(1.0f);
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

    void Model::update(float timeValue){
        angle = timeValue * glm::radians(5.0f); // 0.5 grados por segundo
        model =  glm::rotate(glm::mat4(1.0f), angle ,glm::vec3(0.0,1.0,0.0f)); ;
    }

    void Model::render(glm::mat4 view, glm::mat4 projection){
        
        shader->use();

        // Enviar las matrices al shader
        shader->setMat4x4("model", model);
        shader->setMat4x4("view", view);
        shader->setMat4x4("projection", projection);
        
        // Dibujar el cubo
        glBindVertexArray(VAO);
        glPointSize(4.0f);
        glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, 0);

    }
    void Model::finish(){

        
    std::cout << "Finish Model" << std::endl;
        shader->terminate();
        delete(shader);
        


        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }