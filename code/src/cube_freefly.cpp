#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/Image.hpp>

using namespace glimac;

struct Vertex3DColor
{
    glm::vec3 position;
    glm::vec3 color;

    Vertex3DColor(){
        position.x = 0;
        position.y = 0;
        position.z = 0;
        color.r = 0;
        color.g = 0;
        color.b = 0;
    }
    Vertex3DColor(glm::vec3 pos, glm::vec3 col)
            : position(pos), color(col)
    {
    }

};



int main(int argc, char** argv) {
    // Initialize SDL and open a window
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 800;
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Cube et camera free fly n°128");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/cube.vs.glsl",
                                  applicationPath.dirPath() + "shaders/cube.fs.glsl");
    program.use();

    GLint location_uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    std::cout << "Location uMVPMatrix : " << location_uMVPMatrix << std::endl;

    GLint location_uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    std::cout << "Location uMVMatrix : " << location_uMVMatrix << std::endl;

    GLint location_uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    std::cout << "Location uNormalMatrix : " << location_uNormalMatrix << std::endl;

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    GLuint vbo, vao;
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_TEXTCOORD = 1;
    const GLuint VERTEX_ATTR_NORMALE = 2;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); //Binder la VBO

    Vertex3DColor vertices[] = {
            Vertex3DColor(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1, 0, 0)),
            Vertex3DColor(glm::vec3(0.5, -0.5, -0.5), glm::vec3(1, 0, 0)),
            Vertex3DColor(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(1, 0, 0)),
            Vertex3DColor(glm::vec3(0.5, 0.5, -0.5), glm::vec3(1, 0, 0)),
            Vertex3DColor(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(1, 0, 0)),
            Vertex3DColor(glm::vec3(0.5, -0.5, 0.5), glm::vec3(1, 0, 0)),
            Vertex3DColor(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(1, 0, 0)),
            Vertex3DColor(glm::vec3(0.5, 0.5, 0.5), glm::vec3(1, 0, 0))
    };

    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex3DColor), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // debinder la VBO



    // Creation du IBO Index Buffer Object
    GLuint ibo;
    glGenBuffers(1, &ibo);

    // On bind sur GL_ELEMENT_ARRAY_BUFFER (pour les IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // Tableau d'indices
    uint32_t indices[] = {
            0, 3, 1,
            0, 2, 3,
            0, 2, 6,
            0, 6, 4,
            0, 4, 5,
            0, 5, 1,
            3, 1, 5,
            3, 5, 7,
            2, 3, 7,
            2, 6, 7,
            4, 7, 6,
            4, 7, 5
    };

    // Remplissage de l'IBO avec les indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    // Debind de l'IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); //Binder la VAO

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTCOORD);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMALE);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(
            VERTEX_ATTR_POSITION, /* Indice attribut */
            3, /* Nombre de composantes */
            GL_FLOAT, /* Type d'une composante */
            GL_FALSE, /* Pas de normalisation */
            sizeof(Vertex3DColor), /* Taille en octet d'un vertex complet entre chaque attribut position */
            (const GLvoid*)offsetof(Vertex3DColor, position) /* OpenGL doit utiliser le VBO attaché à GL_ARRAY_BUFFER et commencer à l'offset 0 */
    );
    glVertexAttribPointer(
            VERTEX_ATTR_TEXTCOORD,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex3DColor), /* Taille en octet d'un vertex complet entre chaque attribut position */
            (const GLvoid*)offsetof(Vertex3DColor, color)
    );
    glVertexAttribPointer(
            VERTEX_ATTR_NORMALE,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex3DColor), /* Taille en octet d'un vertex complet entre chaque attribut position */
            0
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); //Debinder la VAO


    glEnable(GL_DEPTH_TEST);


    //Matrices
    glm::mat4 ProjMatrix = glm::perspective (
            glm::radians(70.f), //Angle vertical de vue
            (GLfloat)WINDOW_WIDTH/(GLfloat)WINDOW_HEIGHT, //Ratio fenetre
            0.1f, //near
            100.f //far
    );
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1),glm::vec3(0.f,0.f,0.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    //Camera Trackball
    FreeFlyCamera camera;


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            /*if(e.type == SDL_MOUSEWHEEL)
            {
                if(e.wheel.y > 0) // scroll up
                {
                    std::cout<<"scroll up"<<std::endl;
                    //camera.rotateUp(e.wheel.y);
                    camera.moveFront(e.wheel.y);
                }
                else if(e.wheel.y < 0) // scroll down
                {
                    std::cout<<"scroll down"<<std::endl;
                    //camera.rotateUp(e.wheel.y);
                    camera.moveFront(e.wheel.y);
                }
            }*/

            if(e.type == SDL_MOUSEMOTION && (e.motion.state & SDL_BUTTON_LEFT)){
                camera.rotateLeft(e.motion.xrel);
                camera.rotateUp(e.motion.yrel);
                //std::cout<<"ok ok"<<std::endl;
            }

            if( e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_z) {
                    camera.moveFront(0.5f);
                    //std::cout<<"Z"<<std::endl;
                }
                if (e.key.keysym.sym == SDLK_s) {
                    camera.moveFront(-0.5f);
                    //std::cout<<"S"<<std::endl;
                }
                if (e.key.keysym.sym == SDLK_q) {
                    camera.moveLeft(0.5f);
                    //std::cout<<"Q"<<std::endl;
                }
                if (e.key.keysym.sym == SDLK_d) {
                    camera.moveLeft(-0.5f);
                    //std::cout<<"D"<<std::endl;
                }
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        MVMatrix = camera.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Nettoie le depth buffer à chaque tour aussi

        //std::cout<< camera.getPosition() << std::endl;

        glBindVertexArray(vao); //Binder la VAO

        MVMatrix = glm::translate(MVMatrix,glm::vec3(0.f,0.f,0.f));

        glUniformMatrix4fv(
                location_uMVPMatrix,//location
                1,//number of matrices that will be modified; 1 if it is not an array of matrices
                GL_FALSE,//transpose
                glm::value_ptr(ProjMatrix * MVMatrix) //value
        );
        glUniformMatrix4fv(
                location_uMVMatrix,//location
                1,//number of matrices that will be modified; 1 if it is not an array of matrices
                GL_FALSE,//transpose
                glm::value_ptr(MVMatrix) //value
        );
        glUniformMatrix4fv(
                location_uNormalMatrix,//location
                1,//number of matrices that will be modified; 1 if it is not an array of matrices
                GL_FALSE,//transpose
                glm::value_ptr(NormalMatrix) //value
        );

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0); //Debinder la VAO

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
