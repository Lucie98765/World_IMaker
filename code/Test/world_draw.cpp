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

    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    Scene world(W, L, H);

    Interface interface(argv[0],
        "cube.fs.glsl",
        "cube.vs.glsl",
        world.cubes()[0][0][0].vertices(),
        world.camera().getViewMatrix());

    
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
        interface.draw(world);
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
