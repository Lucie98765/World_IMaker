///
/// \file Interface.cpp
/// \brief source classe Interface
/// \author CHIKAR LESBATS
/// \version 0.1
/// \date 19 dec 2019
///
/// Code source de la classe Interface
///
///


#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#include "glimac/Interface.hpp"

namespace glimac{
	Interface::Interface(std::string path,
		std::string fragment_shader,
		std::string vertex_shader,
		std::vector<glm::vec3> vertices,
		glm::mat4 viewMatrix){

		espace = 1.5f;
		
	    //Shaders
	    std::cout << "load program" << std::endl;
	    FilePath applicationPath(path);
	    Program program = loadProgram(applicationPath.dirPath() + "shaders/"+vertex_shader,
	                                  applicationPath.dirPath() + "shaders/"+fragment_shader);
	    program.use();

	    //Uniform Matrix
	    std::cout << "init uniform matrix" << std::endl;
		uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
	    std::cout << "Location uMVPMatrix : " << uMVPMatrix << std::endl;
	    uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
	    std::cout << "Location uMVMatrix : " << uMVMatrix << std::endl;
	    uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
	    std::cout << "Location uNormalMatrix : " << uNormalMatrix << std::endl;

	    //Uniform Colors
	    std::cout << "init uniform colors" << std::endl;
	    uFaceColor = glGetUniformLocation(program.getGLId(), "uFaceColor");
	    std::cout << "Location uFaceColor : " << uFaceColor << std::endl;
	    uEdgeColor = glGetUniformLocation(program.getGLId(), "uEdgeColor");
	    std::cout << "Location uEdgeColor : " << uEdgeColor << std::endl;
	    uEdgeMode = glGetUniformLocation(program.getGLId(), "uEdgeMode");
	    std::cout << "Location uEdgeMode : " << uEdgeMode << std::endl;

	    //Generation vbo
	    std::cout << "gen vbo" << std::endl;
	    glGenBuffers(1, &vbo);
	    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

	    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);

	    glBindBuffer(GL_ARRAY_BUFFER, 0);

	    //Creation ibo
	    std::cout << "gen ibo" << std::endl;
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


	    //Attribute
	    std::cout << "attrib pointer" << std::endl;
	    const GLuint VERTEX_ATTR_POSITION = 0;
	    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

	    glBindBuffer(GL_ARRAY_BUFFER, vbo);

	    glVertexAttribPointer(
	            VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)0);

	    glBindBuffer(GL_ARRAY_BUFFER, 0);

	    glBindVertexArray(0);

	    //Transparency
	    std::cout << "transparency" << std::endl;
	    glEnable(GL_DEPTH_TEST);
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	    //Matrix
	    std::cout << "init matrix" << std::endl;
	    ProjMatrix = glm::perspective (
            glm::radians(70.f), (GLfloat)WINDOW_WIDTH/(GLfloat)WINDOW_HEIGHT, 0.1f, 100.f);
	    MVMatrix = viewMatrix;
	    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
	}

	Interface::~Interface(){
		glDeleteBuffers(1, &vbo);
	    glDeleteVertexArrays(1, &vao);
	}

	GLuint& Interface::get_vao(){
		return vao;
	}

	void Interface::affect_view(glm::mat4 view, glm::vec3 center, glm::vec3 translate_vector){
		
		float i = translate_vector[0];
		float j = translate_vector[1];
		float k = translate_vector[2];
		MVMatrix = view;
		MVMatrix = glm::translate(MVMatrix,center);
        MVMatrix = glm::translate(MVMatrix,glm::vec3(-0.5f+espace*i,-0.5f+espace*j,-0.5f+espace*k));
	}

	void Interface::affect_uniforms(glm::vec4 fcolor, glm::vec4 ecolor, int edge_mode){
		std::cout << "affect_uniforms" << std::endl;
		glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniform1ui(uEdgeMode, edge_mode);
        glUniform4fv(uFaceColor, 1, glm::value_ptr(fcolor));
        glUniform4fv(uEdgeColor, 1, glm::value_ptr(ecolor));
        if(edge_mode == 1)
        	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
        	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Interface::draw(){
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}