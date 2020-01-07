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

void help(){
    std::cout << "\t *** HOW TO USE WORLD IMAKER ***" << std::endl;
    std::cout << "Press H to see help" << std::endl;
    std::cout << "Press ESCAPE to quit" << std::endl;
    std::cout << "Press 1 to ADD a cube" << std::endl;
    std::cout << "Press 2 to REMOVE a cube" << std::endl;
    std::cout << "Press 3 to EXTRUDE" << std::endl;
    std::cout << "Press 4 to DIG" << std::endl;
    std::cout << "Press 5 to paint in RED" << std::endl;
    std::cout << "Press 6 to paint in YELLOW" << std::endl;
    std::cout << "Press 7 to paint in CYAN" << std::endl;
    std::cout << "Press 8 to paint in GREEN" << std::endl;
    std::cout << "Press 9 to paint in MAGENTA" << std::endl;
    std::cout << "Press left, right, up down, P or M to MOVE CURSOR" << std::endl;
    std::cout << "Press * to SAVE your work" << std::endl;
    std::cout << "Press S to add SUN" << std::endl;
    std::cout << "Press L to add LAMP" << std::endl;
    std::cout << "Press G to GRAB a cube, ESCAPE to cancel, SPACE to validate\n\n" << std::endl;
}

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "World IMaker");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    help();

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/cube.vs.glsl",
                                  applicationPath.dirPath() + "shaders/cube.fs.glsl");
    program.use();

    // UNIFORM MATRIX
        GLint location_uMVPMatrix;
        try{
            location_uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
            if(0 > location_uMVPMatrix)
                throw std::string("Location uMVPMatrix");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }

        GLint location_uMVMatrix;
        try{
            location_uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
            if(0 > location_uMVMatrix)
                throw std::string("Location uMVMatrix");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }

        GLint location_uNormalMatrix;
        try{
            location_uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
            if(0 > location_uNormalMatrix)
                throw std::string("Location uNormalMatrix");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }

    // UNIFORM COLORS
        GLint location_uFaceColor;
        try{
            location_uFaceColor = glGetUniformLocation(program.getGLId(), "uFaceColor");
            if(0 > location_uFaceColor)
                throw std::string("Location uFaceColor");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }

        GLint location_uEdgeColor;
        try{
            location_uEdgeColor = glGetUniformLocation(program.getGLId(), "uEdgeColor");
            if(0 > location_uEdgeColor)
                throw std::string("Location uEdgeColor");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }

        GLint location_uEdgeMode;
        try{
            location_uEdgeMode = glGetUniformLocation(program.getGLId(), "uEdgeMode");
            if(0 > location_uEdgeMode)
                throw std::string("Location uEdgeMode");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }
    
    // UNIFORM DIRECTIONAL LIGHT
        GLint uKd;
        try{
            uKd = glGetUniformLocation(program.getGLId(), "uKd");
            if(0 > uKd)
                throw std::string("Location uKd");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }
        GLint uKs;
        try{
            uKs = glGetUniformLocation(program.getGLId(), "uKs");
            if(0 > uKs)
                throw std::string("Location uKs");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }
        GLint uShininess;
        try{
            uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
            if(0 > uShininess)
                throw std::string("Location uShininess");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }
        GLint uLightDir_vs;
        try{
            uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
            if(0 > uLightDir_vs)
                throw std::string("Location uLightDir_vs");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }
        
        GLint uLightIntensity;
        try{
            uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");
            if(0 > uLightIntensity)
                throw std::string("Location uLightIntensity");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }
        GLint u_is_dir_light;
        try{
            u_is_dir_light = glGetUniformLocation(program.getGLId(), "u_is_dir_light");
            if(0 > u_is_dir_light)
                throw std::string("Location u_is_dir_light");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }
        
    //Point light
        GLint uLightPos_vs;
        try{
            uLightPos_vs = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
            if(0 > uLightPos_vs)
                throw std::string("Location uLightPos_vs");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }
        GLint u_is_point_light;
        try{
            u_is_point_light = glGetUniformLocation(program.getGLId(), "u_is_point_light");
            if(0 > u_is_point_light)
                throw std::string("Location u_is_point_light");
        }
        catch(const std::string &err){
            std::cerr << "Uniform location error : " << err << std::endl;
        }
        
    // BINDING BUFFERS    
    Scene world(3,3,3);
    
    GLuint vbo, vao;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    Cube cube = world.cubes()[0][0][0];

    glBufferData(GL_ARRAY_BUFFER, cube.vertices().size()*sizeof(glm::vec3), &cube.vertices().front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint ibo;
    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

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

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    const GLuint VERTEX_ATTR_NORMAL = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(
            VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*) offsetof(ShapeVertex, position) 
    );
    glVertexAttribPointer(
            VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*) offsetof(ShapeVertex, normal) 
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); 


    glEnable(GL_DEPTH_TEST);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // MATRIX
    glm::mat4 ProjMatrix = glm::perspective (
            glm::radians(70.f), (GLfloat)WINDOW_WIDTH/(GLfloat)WINDOW_HEIGHT, 0.1f, 100.f
    );
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1),glm::vec3(0.f,0.f,-5.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // LOADING SCENE
    std::cout << "Do you want to load a scene ? [y|n] ";
    std::string reponse;
    std::cin >> reponse;

    if(0 == reponse.compare("y")){
        if(!world.load()){
            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);
            return EXIT_FAILURE;
        }
    }
    else{
        // CONFIG PROCEDURAL GENERATION
        std::cout << "Do you want to generate a scene ? [y|n] ";
        std::cin >> reponse;
        if(0 == reponse.compare("y")){  
            if(!world.generate()){
                glDeleteBuffers(1, &vbo);
                glDeleteVertexArrays(1, &vao);
                return EXIT_FAILURE;
            }   
        }
        else{
            // STARTING FROM SCRATCH
            std::cout << "Please enter scene dimensions (width height depth) : ";
            std::cin >> reponse;

            std::stringstream repponse_stream(reponse);
            std::string token;
            std::getline(repponse_stream, token, ' ');

            int w = std::stoi(token);
            std::getline(repponse_stream, token, ' ');
            
            int h = std::stoi(token);
            std::getline(repponse_stream, token, ' ');
            
            int d = std::stoi(token);

            world.width(w);
            world.height(h);
            world.length(d);

            // RECENTERING CURSOR
            for(int i = 0; i < w/2; i++) world.move_cursor(RIGHT);
            for(int i = 0; i < h/2; i++) world.move_cursor(UP);
            for(int i = 0; i < d/2; i++) world.move_cursor(FORWARD);

            // 3 CUBES BASIS
            for(uint i = 0; i < world.width(); i++)
                for(uint j = 0; j < world.length(); j++){
                    world.cubes()[i][0][j].visible(true);
                    world.cubes()[i][1][j].visible(true);
                    world.cubes()[i][2][j].visible(true);
                }
        }
    }

    // SPACE BETWEEN CUBES
    float espace = 1.f;

    // FOR LIGHTS
    bool dir_light = false;
    bool point_light = false;
    float x_light_pos = 1.0f;
    float y_light_pos = 1.0f;
    float z_light_pos = 1.0f;

    // FOR APPLICATION LOOP
    const int W = world.width();
    const int H = world.height();
    const int L = world.length();
    bool done = false;
    bool grabbing = false;
    glm::vec3 origin;
    
    // APPLICATION LOOP
    while(!done) {
        // EVENT LOOP
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true;
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
                switch (e.key.keysym.sym){
                    case SDLK_RETURN:
                        break;
                    case SDLK_h: help();
                        break;
                    case SDLK_ASTERISK:
                        std::cout << "Do you want to save the scene [y|n] ? ";
                        std::cin >> reponse;

                        if(0 == reponse.compare("n"))
                            break;
                        world.save();
                        break;
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
                        if(grabbing){ 
                            world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].edge_color(glm::vec4(0,0,1,1));
                            world.cubes()[origin.x][origin.y][origin.z].selected(true);
                        }
                        break;
                    case SDLK_RIGHT : world.move_cursor(RIGHT);
                        if(grabbing){
                            world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].edge_color(glm::vec4(0,0,1,1));
                            world.cubes()[origin.x][origin.y][origin.z].selected(true);
                        }
                        break;
                    case SDLK_UP : world.move_cursor(UP);
                        if(grabbing){
                            world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].edge_color(glm::vec4(0,0,1,1));
                            world.cubes()[origin.x][origin.y][origin.z].selected(true);
                        }
                        break;
                    case SDLK_DOWN : world.move_cursor(DOWN);
                        if(grabbing){
                            world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].edge_color(glm::vec4(0,0,1,1));
                            world.cubes()[origin.x][origin.y][origin.z].selected(true);
                        }
                        break;
                    case SDLK_m : world.move_cursor(FORWARD);
                        if(grabbing){
                            world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].edge_color(glm::vec4(0,0,1,1));
                            world.cubes()[origin.x][origin.y][origin.z].selected(true);
                        }
                        break;
                    case SDLK_p : world.move_cursor(BACKWARD);
                        if(grabbing){
                            world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].edge_color(glm::vec4(0,0,1,1));
                            world.cubes()[origin.x][origin.y][origin.z].selected(true);
                        }
                        break;
                    case SDLK_ESCAPE :
                        if(grabbing){
                            world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].edge_color(glm::vec4(1,0,0,1));
                            world.cubes()[origin.x][origin.y][origin.z].selected(false);
                            grabbing = false;
                        } 
                        else done = true;
                        break;
                    case SDLK_g : std::cout << "Grabbing" << std::endl;
                        origin = world.cursor();
                        if(!world.cubes()[origin.x][origin.y][origin.z].is_visible())
                            std::cerr << "\tWARNING : Can't grab nothing" << std::endl;
                        else grabbing = true;
                            break;
                    case SDLK_SPACE: 
                        if(!grabbing)
                            break;
                        if(world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].is_visible()){
                            std::cerr << "\tWARNING : Occupied" << std::endl;
                            break;
                        }
                        world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].visible(true);
                        world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].face_color(world.cubes()[origin.x][origin.y][origin.z].face_color());
                        world.cubes()[origin.x][origin.y][origin.z].visible(false);
                        world.cubes()[origin.x][origin.y][origin.z].selected(false);
                        world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].edge_color(glm::vec4(1,0,0,1));
                        grabbing = false;
                        break;
                    case SDLK_s :
                        if(dir_light){
                            std::cout<<"Remove sun" << std::endl;
                            dir_light = false;
                        } else {
                            std::cout<<"Add sun" << std::endl;
                            dir_light = true;
                        }
                        break;
                    case SDLK_l :
                        std::cout<<"Add lamp" << std::endl;
                        if(world.cubes()[world.cursor().x][world.cursor().y][world.cursor().z].is_visible()){
                            std::cerr << "\tWARNING : Occupied" << std::endl;
                            break;
                        }
                        point_light = true;
                        x_light_pos = world.cursor().x;
                        y_light_pos = world.cursor().y;
                        z_light_pos = world.cursor().z;
                        break;                
                    default :
                        std::cerr << "\tWARNING : This command doesn't exist." << std::endl;
                        break;
                }

            }
        }

        // RENDERING
        MVMatrix = world.camera().getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // SENDING UNIFORM VARIABLES TO THE SHADERS
        //Directionnal light
            glm::vec4 lightDir4 =  glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
            lightDir4 = lightDir4 * world.camera().getViewMatrix();
            glm::vec3 lightDir = glm::vec3(lightDir4.x, lightDir4.y, lightDir4.z);

            glUniform3fv(uKd, 1,  glm::value_ptr(glm::vec3(3.f, 1.f, 2.f)));
            glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(2.f, 1.f, 0.1f)));
            glUniform1f(uShininess,0.5f);
            glUniform3fv(uLightDir_vs, 1, glm::value_ptr(lightDir));
            glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(.5f, .5f, .5f)));
            glUniform1ui(u_is_dir_light, dir_light);

        //Point light
            glm::vec4 lightPos =  glm::vec4(x_light_pos, y_light_pos, z_light_pos, 0.0f);
            lightPos = lightPos * world.camera().getViewMatrix();
            glm::vec3 lightPos_send = glm::vec3(lightPos.x, lightPos.y, lightPos.z);
            glUniform3fv(uLightPos_vs, 1, glm::value_ptr(lightPos_send));
            glUniform1ui(u_is_point_light, point_light);


        glBindVertexArray(vao); 

        glUniform1ui(location_uEdgeMode, false);

        // DRAWING VISIBLE CUBES
        for(uint i = 0; i < world.width(); i++){
            for(uint j = 0; j < world.height(); j++){
                for(uint k = 0; k < world.length(); k++){
                    if(world.cubes()[i][j][k].is_visible()){
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

        // DRAWING INVISIBLE CUBES
        for(uint i = 0; i < world.width(); i++){
            for(uint j = 0; j < world.height(); j++){
                for(uint k = 0; k < world.length(); k++){
                    if(!world.cubes()[i][j][k].is_visible()){
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

        // DRAWING SELECTED CUBES
        for(uint i = 0; i < world.width(); i++){
            for(uint j = 0; j < world.height(); j++){
                for(uint k = 0; k < world.length(); k++){
                    if(world.cubes()[i][j][k].is_selected()){
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
