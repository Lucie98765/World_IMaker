#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>
#include <glimac/Image.hpp>
#include <fstream>
#include <math.h>

#include <glimac/Cube.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Scene.hpp>
#include <glimac/RBF.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

using namespace glimac;


int main(int argc, char** argv) {
    if(4 != argc){
        std::cerr << "usage " << argv[0] << " width height depth" << std::endl;
        return EXIT_FAILURE;
    }
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

    //Uniforms
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


    //Directionnal light
    GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
    std::cout << "Location uKd : " << uKd << std::endl;
    GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
    std::cout << "Location uKs : " << uKs << std::endl;
    GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
    std::cout << "Location uShininess : " << uShininess << std::endl;
    GLint uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
    std::cout << "Location uLightDir_vs : " << uLightDir_vs << std::endl;
    GLint uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");
    std::cout << "Location uLightIntensity : " << uLightIntensity << std::endl;
    GLint u_is_dir_light = glGetUniformLocation(program.getGLId(), "u_is_dir_light");
    std::cout << "Location u_is_dir_light : " << u_is_dir_light << std::endl;

    //Point light
    GLint uLightPos_vs = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
    std::cout << "Location uLightPos_vs : " << uLightPos_vs << std::endl;
    GLint u_is_point_light = glGetUniformLocation(program.getGLId(), "u_is_point_light");
    std::cout << "Location u_is_point_light : " << u_is_point_light << std::endl;



    const int W = std::stoi(argv[1]);
    const int H = std::stoi(argv[2]);
    const int L = std::stoi(argv[3]);

    Scene world(W, H, L);
    
    GLuint vbo, vao;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); //Binder la VBO

    Cube cube = world.cubes()[0][0][0];

    glBufferData(GL_ARRAY_BUFFER, cube.vertices().size()*sizeof(glm::vec3), &cube.vertices().front(), GL_STATIC_DRAW);

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
    const GLuint VERTEX_ATTR_NORMAL = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(
            VERTEX_ATTR_POSITION, /* Indice attribut */
            3, /* Nombre de composantes */
            GL_FLOAT, /* Type d'une composante */
            GL_FALSE, /* Pas de normalisation */
            sizeof(glm::vec3), /* Taille en octet d'un vertex complet entre chaque attribut position */
            (const GLvoid*) offsetof(ShapeVertex, position) /* OpenGL doit utiliser le VBO attaché à GL_ARRAY_BUFFER et commencer à l'offset 0 */
    );
    glVertexAttribPointer(
            VERTEX_ATTR_NORMAL, /* Indice attribut */
            3, /* Nombre de composantes */
            GL_FLOAT, /* Type d'une composante */
            GL_FALSE, /* Pas de normalisation */
            sizeof(glm::vec3), /* Taille en octet d'un vertex complet entre chaque attribut position */
            (const GLvoid*) offsetof(ShapeVertex, normal) /* OpenGL doit utiliser le VBO attaché à GL_ARRAY_BUFFER et commencer à l'offset 0 */
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

    // CONFIG INIT
    std::cout << "Do you want to generate a scene ? [y|n] ";
    std::string reponse;
    std::cin >> reponse;


    if(0 == reponse.compare("y")){
        std::cout << "\nPlease select a config file" << std::endl;
        std::string config;
        std::cin >> config;

        std::ifstream confFile("/home/louisa/IMAC2/POO/World_IMaker/code/Test/"+config);
        if(!confFile.is_open())
            std::cerr << "Couldn't open config file" << std::endl;
        else
            std::cout << config << " opened successfuly" << std::endl;
        std::string w, h, l, phi, display, nb_pts_ctrl;

        std::getline(confFile, w); 
        std::getline(confFile, h); 
        std::getline(confFile, l); 
        std::getline(confFile, phi);
        std::getline(confFile, display);
        std::getline(confFile, nb_pts_ctrl);

        //init scene
        world.width(std::stoi(w));
        world.height(std::stoi(h));
        world.length(std::stoi(l));

        //affect phi func
        std::function<float (glm::vec3 x, glm::vec3 y)> func;

        std::function<float (glm::vec3 x, glm::vec3 y)> exp_phi = [](glm::vec3 x, glm::vec3 y){
            return exp(0.001*abs(glm::distance(x,y))*abs(glm::distance(x,y)));};
        std::function<float (glm::vec3 x, glm::vec3 y)> lin_phi = [](glm::vec3 x, glm::vec3 y){
            return 0.001*abs(glm::distance(x,y))*abs(glm::distance(x,y));};
        std::function<float (glm::vec3 x, glm::vec3 y)> sqrt_phi = [](glm::vec3 x, glm::vec3 y){
            return sqrt(1+pow(0.001*abs(glm::distance(x,y))*abs(glm::distance(x,y)),2));};
        std::function<float (glm::vec3 x, glm::vec3 y)> rat_phi = [](glm::vec3 x, glm::vec3 y){
            return 1/(1+pow(0.001*abs(glm::distance(x,y))*abs(glm::distance(x,y)),2));};

        if(0 == phi.compare("exp"))
            func = exp_phi;
        if(0 == phi.compare("lin"))
            func = lin_phi;
        if(0 == phi.compare("sqrt"))
            func = sqrt_phi;
        if(0 == phi.compare("rat"))
            func = rat_phi;

        // Cube matrix
        std::vector<glm::vec3> cube_matrix(world.width()*world.height()*world.length());
        for(uint i = 0; i < world.width(); i++)
            for(uint j = 0; j < world.width(); j++)
                for(uint k = 0; k < world.width(); k++)
                    cube_matrix[i*k*k+j*k+k] = glm::vec3(i,j,k);

        // init RBF
        RBF rbf(std::stoi(nb_pts_ctrl));
        int i = 0;
        std::string pt_ctrl;
        std::vector<glm::vec3> list_pts_ctrl(stoi(nb_pts_ctrl));
        int x, y, z;


        //Case control points given
        for(; std::getline(confFile, pt_ctrl); i++){
            std::stringstream ss(pt_ctrl);
            std::string token;
            while(std::getline(ss, token, ' ')){
                x = std::stoi(token);
                std::getline(ss, token, ' ');
                
                y = std::stoi(token);
                std::getline(ss, token, ' ');
                
                z = std::stoi(token);

                list_pts_ctrl[i] = (glm::vec3(x,y,z));  
            }


        }
        if(0 < i)
            rbf.build(cube_matrix, list_pts_ctrl, func);

        //Case nb control points given
        else
            rbf.build(cube_matrix, std::stoi(nb_pts_ctrl), func);
        
        //Calculation interpolated values
        std::vector<float> g_p(cube_matrix.size());
        for(size_t i = 0; i < g_p.size(); i++)
            g_p[i] = rbf.g(cube_matrix[i]);

        //Affect display condition
        std::function<bool (glm::vec3, float)> predicate;
        float pivot;

        if(0 == display.compare("moy")){
            predicate = [rbf](glm::vec3 p, float pivot) mutable {
                                return 0.001 >= abs(rbf.g(p) - pivot);
                            };
            pivot = std::accumulate(g_p.begin(), g_p.end(), 0.f)/g_p.size();
        }

        else{
            predicate = [rbf](glm::vec3 p, float pivot) mutable {
                        return rbf.g(p) >= pivot;
            };
            pivot = stoi(display);
        }

        //Update visibility of cubes
        for(uint i = 0; i < world.width(); i++){
            for(uint j = 0; j < world.height(); j++){
                for(uint k = 0; k < world.length(); k++){
                    world.cubes()[i][j][k].visible(
                        rbf.is_displayable(cube_matrix[i*k*k+j*k+k], 
                            pivot, predicate));

                    // if(world.cubes()[i][j][k].is_visible())
                    //     std::cout << "\t";
                    // std::cout << "update display (" << i << ", " << j << ", " << k << ") ===> " << world.cubes()[i][j][k].is_visible() << std::endl;
                }
            }
        }        
    }

    // Test data
        // std::cout << std::endl;
        // std::cout << "World " << world.width() << "x" << world.height() << "x"<< world.length() << std::endl;
        // Cube cube0 = world.cubes()[0][0][0];
        // std::cout << "Cubes vertices (" << cube0.vertices().size() << ")" << std::endl;
        // for(int i = 0; i < cube0.vertices().size(); i++)
        //     std::cout <<(cube0.vertices())[i] << std::endl;

        // for(int i = 0; i < world.width(); i++){
        //     for(int j = 0; j < world.height(); j++){
        //         for(int k = 0; k < world.length(); k++){
        //             if((world.cubes()[i][j][k]).is_visible())
        //                 std::cout << "\t";
        //             std::cout << "Cube (" << i << ", " << j << ", " << k<< ") is visible ? "<< (world.cubes()[i][j][k]).is_visible() << std::endl;
        //             std::cout << "Cube (" << i << ", " << j << ", " << k<< ") is selected ? "<< (world.cubes()[i][j][k]).is_selected() << std::endl;
        //         }
        //     }
        // }

        // std::cout << "Cursor " << world.cursor() << std::endl;
        // std::cout << "Camera \n" << world.camera().getViewMatrix() << std::endl;
   
    float espace = 1.f;



    //For lights
    bool dir_light = false;
    bool point_light = false;
    float x_light_pos = 1.0f;
    float y_light_pos = 1.0f;
    float z_light_pos = 1.0f;


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
                world.camera().moveFront(e.wheel.y);
            }

            if(e.type == SDL_MOUSEMOTION && (e.motion.state & SDL_BUTTON_LEFT)){
                world.camera().rotateLeft(e.motion.yrel);
                world.camera().rotateUp(e.motion.xrel); 
            }

            if( e.type == SDL_KEYDOWN){
                std::cout << e.key.keysym.sym << std::endl;
                switch (e.key.keysym.sym){
                    case SDLK_1 :
                        std::cout<<"Create a new cube" << std::endl;
                        world.add_cube();
                        break;
                    case SDLK_2 :
                        std::cout<<"Delete this cube" << std::endl;
                        world.delete_cube();
                        break;
                    case SDLK_3 :
                        std::cout<<"Extrude" << std::endl;
                        world.extrude_cube();
                        break;
                    case SDLK_4 :
                        std::cout<<"Dig" << std::endl;
                        world.dig_cube();
                        break;
                    case SDLK_5 :
                        std::cout<<"Paint in red" << std::endl;
                        world.change_color(glm::vec4(1, 0, 0, 1));
                        break;
                    case SDLK_6 :
                        std::cout<<"Paint in yellow" << std::endl;
                        world.change_color(glm::vec4(1, 1, 0, 1));
                        break;
                    case SDLK_7 :
                        std::cout<<"Paint in cyan" << std::endl;
                        world.change_color(glm::vec4(0, 1, 1, 1));
                        break;
                    case SDLK_8 :
                        std::cout<<"Paint in green" << std::endl;
                        world.change_color(glm::vec4(0, 1, 0, 1));
                        break;
                    case SDLK_9 :
                        std::cout<<"Paint in magenta" << std::endl;
                        world.change_color(glm::vec4(1, 0, 1, 1));
                        break;
                    case SDLK_LEFT : world.move_cursor(LEFT);
                        break;
                    case SDLK_RIGHT : world.move_cursor(RIGHT);
                        break;
                    case SDLK_UP : world.move_cursor(UP);
                        break;
                    case SDLK_DOWN : world.move_cursor(DOWN);
                        break;
                    //case SDLK_KP_PLUS :
                    case SDLK_p : world.move_cursor(FORWARD);
                        break;
                    //case SDLK_KP_MINUS :
                    case SDLK_m : world.move_cursor(BACKWARD);
                        break;
                    case SDLK_s :
                        std::cout<<"Add sun light" << std::endl;
                        if(dir_light){
                            dir_light = false;
                        } else {
                            dir_light = true;
                        }
                        break;
                    case SDLK_l :
                        std::cout<<"Add lamp light" << std::endl;
                        point_light = true;
                        x_light_pos = world.cursor().x;
                        y_light_pos = world.cursor().y;
                        z_light_pos = world.cursor().z;
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

        MVMatrix = world.camera().getViewMatrix();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Sending uniform variables to the shader
        //Directionnal light
        glm::vec4 lightDir4 =  glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        lightDir4 = lightDir4 * world.camera().getViewMatrix();
        glm::vec3 lightDir = glm::vec3(lightDir4.x, lightDir4.y, lightDir4.z);

        glUniform3fv(uKd, 1,  glm::value_ptr(glm::vec3(3.f, 1.f, 2.f)));
        glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(2.f, 1.f, 0.1f)));
        glUniform1f(uShininess,0.5f);
        glUniform3fv(uLightDir_vs, 1, glm::value_ptr(lightDir));
        glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(1.f, 1.f, 1.f)));
        glUniform1ui(u_is_dir_light, dir_light);

        //Point light
        glm::vec4 lightPos =  glm::vec4(x_light_pos, y_light_pos, z_light_pos, 0.0f);
        lightPos = lightPos * world.camera().getViewMatrix();
        glm::vec3 lightPos_send = glm::vec3(lightPos.x, lightPos.y, lightPos.z);
        glUniform3fv(uLightPos_vs, 1, glm::value_ptr(lightPos_send));
        glUniform1ui(u_is_point_light, point_light);



        glBindVertexArray(vao); 

        glUniform1ui(location_uEdgeMode, false);

        

        for(uint i = 0; i < world.width(); i++){
            for(uint j = 0; j < world.height(); j++){
                for(uint k = 0; k < world.length(); k++){
                    if(world.cubes()[i][j][k].is_visible()){
                        // std::cout << "DRAW visible " << i << ", " << j << ", " << k <<std::endl;
                        MVMatrix = world.camera().getViewMatrix();
                        MVMatrix = glm::translate(MVMatrix,glm::vec3(-W/2, -H/2, -L/2));
                        MVMatrix = glm::translate(MVMatrix,glm::vec3(-0.5f+espace*i,-0.5f+espace*j,-0.5f+espace*k));

                        glUniformMatrix4fv(location_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(location_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(location_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                        glUniform4fv(location_uFaceColor, 1, glm::value_ptr(world.cubes()[i][j][k].face_color()));
                        glUniform4fv(location_uEdgeColor, 1, glm::value_ptr(world.cubes()[i][j][k].edge_color()));
                        
                        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                    }
                }
            }
        }

        for(uint i = 0; i < world.width(); i++){
            for(uint j = 0; j < world.height(); j++){
                for(uint k = 0; k < world.length(); k++){
                    if(!world.cubes()[i][j][k].is_visible()){
                        // std::cout << "DRAW invisible " << i << ", " << j << ", " << k <<std::endl;

                        MVMatrix = world.camera().getViewMatrix();
                        MVMatrix = glm::translate(MVMatrix,glm::vec3(-W/2, -H/2, -L/2));
                        MVMatrix = glm::translate(MVMatrix,glm::vec3(-0.5f+espace*i,-0.5f+espace*j,-0.5f+espace*k));

                        glUniformMatrix4fv(location_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(location_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(location_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                        glUniform4fv(location_uFaceColor, 1, glm::value_ptr(world.cubes()[i][j][k].face_color()));
                        glUniform4fv(location_uEdgeColor, 1, glm::value_ptr(world.cubes()[i][j][k].edge_color()));

                        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                    }
                }
            }
        }

        for(uint i = 0; i < world.width(); i++){
            for(uint j = 0; j < world.height(); j++){
                for(uint k = 0; k < world.length(); k++){
                    if(world.cubes()[i][j][k].is_selected()){
                        // std::cout << "DRAW selected " << i << ", " << j << ", " << k <<std::endl;

                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        glUniform1i(location_uEdgeMode, true);
                        MVMatrix = world.camera().getViewMatrix();
                        MVMatrix = glm::translate(MVMatrix,glm::vec3(-W/2, -H/2, -L/2));
                        MVMatrix = glm::translate(MVMatrix,glm::vec3(-0.5f+espace*i,-0.5f+espace*j,-0.5f+espace*k));

                        glUniformMatrix4fv(location_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                        glUniformMatrix4fv(location_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                        glUniformMatrix4fv(location_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                        glUniform4fv(location_uFaceColor, 1, glm::value_ptr(world.cubes()[i][j][k].face_color()));
                        glUniform4fv(location_uEdgeColor, 1, glm::value_ptr(world.cubes()[i][j][k].edge_color()));

                        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

                    }
                }
            }
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                 

        glBindVertexArray(0);
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
