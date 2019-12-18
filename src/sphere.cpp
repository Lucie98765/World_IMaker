

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/directionallight.fs.glsl");
    program.use();

    GLint location_uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    std::cout << "Location uMVPMatrix : " << location_uMVPMatrix << std::endl;

    GLint location_uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    std::cout << "Location uMVMatrix : " << location_uMVMatrix << std::endl;

    GLint location_uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    std::cout << "Location uNormalMatrix : " << location_uNormalMatrix << std::endl;

    GLint location_uKd = glGetUniformLocation(program.getGLId(), "uKd");
    std::cout << "Location uKd : " << location_uKd << std::endl;

    GLint location_uKs = glGetUniformLocation(program.getGLId(), "uKs");
    std::cout << "Location uKs : " << location_uKs << std::endl;

    GLint location_uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
    std::cout << "Location uShininess : " << location_uShininess << std::endl;

    GLint location_uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
    std::cout << "Location uLightDir_vs : " << location_uLightDir_vs << std::endl;

    GLint location_uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");
    std::cout << "Location uLightIntensity : " << location_uLightIntensity << std::endl;


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;



    // Application loop:
    bool done = false;
    while(!done) {
        
        /*Envoi des variables uniformes au shader */
        glm::vec4 lightDir4 =  glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        lightDir4 = lightDir4 * camera.getViewMatrix();
        glm::vec3 lightDir = glm::vec3(lightDir.x, lightDir.y, lightDir.z);

        glUniform3fv(location_uKd,1,  glm::value_ptr(glm::vec3(0.2f, 0.3f, 0.2f)));
        glUniform3fv(location_uKs,1, glm::value_ptr(glm::vec3(0.5f, 0.1f, 0.4f)));
        glUniform1f(location_uShininess, 0.8f);
        glUniform3fv(location_uLightDir_vs,1, glm::value_ptr(lightDir));
        glUniform3fv(location_uLightIntensity,1, glm::value_ptr(glm::vec3(5.f, 4.f, 7.f)));


}

