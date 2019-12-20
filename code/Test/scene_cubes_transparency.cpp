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
    GLint location_uEdgeMode = glGetUniformLocation(program.getGLId(), "uEdgeMode");
    std::cout << "Location uEdgeMode : " << location_uEdgeMode << std::endl;

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


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Matrices
    glm::mat4 ProjMatrix = glm::perspective (
            glm::radians(70.f), //Angle vertical de vue
            (GLfloat)WINDOW_WIDTH/(GLfloat)WINDOW_HEIGHT, //Ratio fenetre
            0.1f, //near
            100.f //far
    );
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1),glm::vec3(0.f,0.f,-5.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    //Trackball Camera
    TrackballCamera camera;
    glm::mat4 cameraVM(1);


    //Cursor
    glm::vec3 cursor;
    cursor = glm::vec3(1, 0, 0);


    Cube scene[W][H][L];
    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            for(int k = 0; k < L; k++){
                scene[i][j][k] = Cube();
                (scene[i][j][k]).visible(true);
                (scene[i][j][k]).selected(false);
            }
        }
    }

    (scene[1][0][0]).visible(false);
    (scene[1][0][0]).selected(true);
    /*(scene[0][0][2]).visible(false);
    (scene[0][0][2]).selected(true);
    
    (scene[2][0][0]).visible(false);
    (scene[2][0][0]).selected(true);
    (scene[2][0][2]).visible(false);
    (scene[2][0][2]).selected(true);
    
    (scene[0][2][0]).visible(false);
    (scene[0][2][0]).selected(true);
    (scene[0][2][2]).visible(false);
    (scene[0][2][2]).selected(true);
    
    (scene[2][2][0]).visible(false);
    (scene[2][2][0]).selected(true);
    (scene[2][2][2]).visible(false);
    (scene[2][2][2]).selected(true);*/


    float espace = 1.5f;
    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            if(e.type == SDL_MOUSEWHEEL)
            {
                camera.moveFront(e.wheel.y);
            }

            if(e.type == SDL_MOUSEMOTION && (e.motion.state & SDL_BUTTON_LEFT)){
                camera.rotateLeft(e.motion.yrel);
                camera.rotateUp(e.motion.xrel); 
            }

            if( e.type == SDL_KEYDOWN){
                std::cout << e.key.keysym.sym << std::endl;
                switch (e.key.keysym.sym){
                    case SDLK_1 :
                        std::cout<<"Create a new cube" << std::endl;
                        break;
                    case SDLK_2 :
                        std::cout<<"Delete this cube" << std::endl;
                        break;
                    case SDLK_3 :
                        std::cout<<"Extrude" << std::endl;
                        break;
                    case SDLK_4 :
                        std::cout<<"Dig" << std::endl;
                        break;
                    case SDLK_5 :
                        std::cout<<"Paint in red" << std::endl;
                        break;
                    case SDLK_6 :
                        std::cout<<"Paint in yellow" << std::endl;
                        break;
                    case SDLK_7 :
                        std::cout<<"Paint in cyan" << std::endl;
                        break;
                    case SDLK_8 :
                        std::cout<<"Paint in green" << std::endl;
                        break;
                    case SDLK_9 :
                        std::cout<<"Paint in magenta" << std::endl;
                        break;
                    case SDLK_LEFT :
                        if (cursor[0] > 0){
                            //std::cout<< "left" << cursor[0] << std::endl;
                            int current_x = cursor[0];
                            int current_y = cursor[1];
                            int current_z = cursor[2];
                            scene[current_x][current_y][current_z].selected(false);
                            scene[current_x - 1][current_y][current_z].selected(true);
                            cursor = glm::vec3 (current_x-1, current_y, current_z);
                        }
                        break;
                    case SDLK_RIGHT :
                        if (cursor[0] < W){
                            //std::cout<< "right"<< cursor[0] << std::endl;
                            int current_x = cursor[0];
                            int current_y = cursor[1];
                            int current_z = cursor[2];
                            scene[current_x][current_y][current_z].selected(false);
                            scene[current_x + 1][current_y][current_z].selected(true);
                            cursor = glm::vec3 (current_x+1, current_y, current_z);
                        }
                        break;
                    case SDLK_UP :
                        if (cursor[1] < H){
                            //std::cout<< "up"<< cursor[1] << std::endl;
                            int current_x = cursor[0];
                            int current_y = cursor[1];
                            int current_z = cursor[2];
                            scene[current_x][current_y][current_z].selected(false);
                            scene[current_x][current_y+1][current_z].selected(true);
                            cursor = glm::vec3 (current_x, current_y+1, current_z);
                        }
                        break;
                    case SDLK_DOWN :
                        if (cursor[1] > 0){
                            //std::cout<< "down"<< cursor[1] << std::endl;
                            int current_x = cursor[0];
                            int current_y = cursor[1];
                            int current_z = cursor[2];
                            scene[current_x][current_y][current_z].selected(false);
                            scene[current_x][current_y-1][current_z].selected(true);
                            cursor = glm::vec3 (current_x, current_y-1, current_z);
                        }
                        break;
                    case SDLK_o :
                        if (cursor[2] < L){
                            //std::cout<< "far "<< cursor[2] << std::endl;
                            int current_x = cursor[0];
                            int current_y = cursor[1];
                            int current_z = cursor[2];
                            scene[current_x][current_y][current_z].selected(false);
                            scene[current_x][current_y][current_z+1].selected(true);
                            cursor = glm::vec3 (current_x, current_y, current_z+1);
                        }
                        break;
                    case SDLK_l :
                        if (cursor[2] > 0){
                            //std::cout<< "near "<< cursor[2] << std::endl;
                            int current_x = cursor[0];
                            int current_y = cursor[1];
                            int current_z = cursor[2];
                            scene[current_x][current_y][current_z].selected(false);
                            scene[current_x][current_y][current_z-1].selected(true);
                            cursor = glm::vec3 (current_x, current_y, current_z-1);
                        }
                        break;
                    case SDLK_ESCAPE :
                        done = true;
                        break;
                    default :
                        std::cout << "This command doesn't exist." << std::endl;
                        break;
                }

            }
        }



        MVMatrix = camera.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBindVertexArray(vao); 

        glUniform1ui(location_uEdgeMode, 0);

        //std::cout << "Centre " << glm::vec3(W/2, H/2, L/2) << std::endl;
        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){
                for(int k = 0; k < L; k++){
                    Cube current = scene[i][j][k];

                    if(current.is_visible()){
                    //std::cout << "Décalage " << glm::vec3(k,j,i) << std::endl;
                    //std::cout << "\t==> " << glm::vec3(k-W/2,j-H/2,i-L/2) << std::endl;

                    MVMatrix = camera.getViewMatrix();
                    MVMatrix = glm::translate(MVMatrix,glm::vec3(-W/2, -H/2, -L/2));
                    MVMatrix = glm::translate(MVMatrix,glm::vec3(-0.5f+espace*i,-0.5f+espace*j,-0.5f+espace*k));

                    glUniformMatrix4fv(location_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glUniformMatrix4fv(location_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(location_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                    glUniform4fv(location_uFaceColor, 1, glm::value_ptr(current.face_color()));
                    glUniform4fv(location_uEdgeColor, 1, glm::value_ptr(current.edge_color()));
                    
                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                    //std::cout<<i<< j<< k <<std::endl;
                    }
                }
            }
        }

        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){
                for(int k = 0; k < L; k++){
                    Cube current = scene[i][j][k];
                    if(!current.is_visible()){
                    //std::cout << "Décalage " << glm::vec3(k,j,i) << std::endl;
                    //std::cout << "\t==> " << glm::vec3(k-W/2,j-H/2,i-L/2) << std::endl;

                    MVMatrix = camera.getViewMatrix();
                    MVMatrix = glm::translate(MVMatrix,glm::vec3(-W/2, -H/2, -L/2));
                    MVMatrix = glm::translate(MVMatrix,glm::vec3(-0.5f+espace*i,-0.5f+espace*j,-0.5f+espace*k));

                    glUniformMatrix4fv(location_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glUniformMatrix4fv(location_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(location_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                    glUniform4fv(location_uFaceColor, 1, glm::value_ptr(current.face_color()));
                    glUniform4fv(location_uEdgeColor, 1, glm::value_ptr(current.edge_color()));

                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                    //std::cout<<i<< j<< k <<std::endl;
                    }
                }
            }
        }

        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){
                for(int k = 0; k < L; k++){
                    Cube current = scene[i][j][k];
                    if(current.is_selected()){

                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        glUniform1i(location_uEdgeMode, 1);
                        MVMatrix = camera.getViewMatrix();
                        MVMatrix = glm::translate(MVMatrix,glm::vec3(-W/2, -H/2, -L/2));
                        MVMatrix = glm::translate(MVMatrix,glm::vec3(-0.5f+espace*i,-0.5f+espace*j,-0.5f+espace*k));

                        glUniformMatrix4fv(location_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(location_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(location_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                        glUniform4fv(location_uFaceColor, 1, glm::value_ptr(current.face_color()));
                        glUniform4fv(location_uEdgeColor, 1, glm::value_ptr(current.edge_color()));

                        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                        //std::cout<<i<< j<< k <<std::endl;
                    }
                }
            }
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //done = true;


                 

        glBindVertexArray(0);
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
