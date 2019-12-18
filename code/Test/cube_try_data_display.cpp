#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Image.hpp>

#include <glimac/Cube.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define W 3
#define L 3
#define H 3

using namespace glimac;


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Dessin de cube please");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


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


    GLint location_uFaceColor = glGetUniformLocation(program.getGLId(), "uFaceColor");
    std::cout << "Location uFaceColor : " << location_uFaceColor << std::endl;
    GLint location_uEdgeColor = glGetUniformLocation(program.getGLId(), "uEdgeColor");
    std::cout << "Location uEdgeColor : " << location_uEdgeColor << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    GLuint vbo, vao;

    Cube cube;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); //Binder la VBO

    glm::vec3 vertices[] = {
            glm::vec3(-0.5, -0.5, -0.5),
            glm::vec3(0.5, -0.5, -0.5),
            glm::vec3(-0.5, 0.5, -0.5),
            glm::vec3(0.5, 0.5, -0.5),
            glm::vec3(-0.5, -0.5, 0.5),
            glm::vec3(0.5, -0.5, 0.5),
            glm::vec3(-0.5, 0.5, 0.5),
            glm::vec3(0.5, 0.5, 0.5)
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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


    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(
            VERTEX_ATTR_POSITION, /* Indice attribut */
            3, /* Nombre de composantes */
            GL_FLOAT, /* Type d'une composante */
            GL_FALSE, /* Pas de normalisation */
            sizeof(glm::vec3), /* Taille en octet d'un vertex complet entre chaque attribut position */
            (const GLvoid*)0 /* OpenGL doit utiliser le VBO attaché à GL_ARRAY_BUFFER et commencer à l'offset 0 */
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
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1),glm::vec3(0.f,0.f,-5.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    //Camera Trackball
    TrackballCamera camera;
    glm::mat4 cameraVM(1);

    cube.visible(true);
    cube.selected(true);
    std::cout << "Cube visible ? " << cube.is_visible() << std::endl; 
    std::cout << "Cube selectionné ? " << cube.is_selected() << std::endl;
    std::cout << "Couleur face : " << cube.face_color() << std::endl;
    std::cout << "Couleur arete : " << cube.edge_color() << std::endl;
    glUniform4fv(location_uFaceColor, 1, glm::value_ptr(cube.face_color()));
    glUniform4fv(location_uEdgeColor, 1, glm::value_ptr(cube.edge_color()));

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT || ( e.type == SDL_KEYDOWN 
                && e.key.keysym.sym == SDLK_ESCAPE)) {
                done = true; // Leave the loop after this iteration
            }

            if(e.type == SDL_MOUSEWHEEL)
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
            }

            if(e.type == SDL_MOUSEMOTION && (e.motion.state & SDL_BUTTON_LEFT)){
                camera.rotateLeft(e.motion.xrel);
                camera.rotateUp(e.motion.yrel); //A voir si on met -xrel et -yrel, voir si c'est plus intuitif
                //std::cout<< e.motion.yrel <<std::endl;
            }
        }



        MVMatrix = camera.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBindVertexArray(vao); 


        if(cube.is_visible()){
            MVMatrix = glm::translate(MVMatrix,glm::vec3(0.f,0.f,0.f));
            glUniformMatrix4fv(location_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(location_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(location_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }           

        glBindVertexArray(0);
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
