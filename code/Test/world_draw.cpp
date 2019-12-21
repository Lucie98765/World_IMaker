#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>
#include <glimac/Image.hpp>
#include <string>

#include <glimac/Cube.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Interface.hpp>


#define W 3
#define L 3
#define H 3

using namespace glimac;


int main(int argc, char** argv) {
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "World Imaker");
    std::cout<<"test 1"<<std::endl;

    
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    Scene world(W, L, H);

    std::string path = argv[0];
    std::vector<glm::vec3> vertices = world.cubes()[0][0][0].vertices();
    glm::mat4 viewMatrix = world.camera().getViewMatrix();

    std::cout << "path : " << path << std::endl;

    std::cout<<"test vertices" << std::endl;
    for(int i = 0; i < vertices.size(); i++)
        std::cout << vertices[i]<<std::endl;

    std::cout << "test camera" << viewMatrix << std::endl;

    std::string fragment_shader = "cube.fs.glsl";
    std::string vertex_shader = "cube.vs.glsl";
    std::cout << "Fragment Shader : " << fragment_shader << std::endl;
    std::cout << "Vertex Shader : " << fragment_shader << std::endl;

    // Interface interface(path,
    //     fragment_shader,
    //     vertex_shader,
    //     vertices,
    //     viewMatrix);

    Interface interface;
    
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
                    case SDLK_ESCAPE :
                        done = true;
                        break;
                    default :
                        std::cout << "This command doesn't exist." << std::endl;
                        break;
                }

            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBindVertexArray(interface.get_vao()); 

        for(int i = 0; i < world.width(); i++){
            for(int j = 0; j < world.height(); j++){
                for(int k = 0; k < world.length(); k++){
                    if(world.cubes()[i][j][k].is_visible()){
                        interface.affect_uniforms(world.cubes()[i][j][k].face_color(), world.cubes()[i][j][k].edge_color(), 0);
                        interface.draw();
                    }
                }
            }
        }

        for(int i = 0; i < world.width(); i++){
            for(int j = 0; j < world.height(); j++){
                for(int k = 0; k < world.length(); k++){
                    if(!world.cubes()[i][j][k].is_visible()){
                        interface.affect_uniforms(world.cubes()[i][j][k].face_color(), world.cubes()[i][j][k].edge_color(), 0);
                        interface.draw();
                    }
                }
            }
        }

        for(int i = 0; i < world.width(); i++){
            for(int j = 0; j < world.height(); j++){
                for(int k = 0; k < world.length(); k++){
                    if(world.cubes()[i][j][k].is_selected()){
                        interface.affect_uniforms(world.cubes()[i][j][k].face_color(), world.cubes()[i][j][k].edge_color(), 1);
                        interface.draw();

                    }
                }
            }
        }

        //done = true;

        glBindVertexArray(0);
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
