///
/// \file Interface.hpp
/// \brief header classe Interface
/// \author CHIKAR LESBATS
/// \version 0.1
/// \date 19 dec 2019
///
/// Header de la classe Interface
///
///


#pragma once 

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>
#include "common.hpp"
#include <vector>

#include "glimac/Scene.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define FRAG_SHAD "cube.fs.glsl"
#define VERT_SHAD "cube.vs.glsl"

namespace glimac{
	class Interface{
		private:
			Program program;

			GLint uMVPMatrix;
			GLint uMVMatrix;
			GLint uNormalMatrix;

			glm::mat4 ProjMatrix;
			glm::mat4 MVMatrix;
			glm::mat4 NormalMatrix;

			GLint uFaceColor;
			GLint uEdgeColor;
			GLint uEdgeMode;

			GLuint vbo;
			GLuint vao;
			GLuint ibo;

			float espace;

		public:
			Interface(std::string path,
				std::string fragment_shader,
				std::string vertex_shader,
				std::vector<glm::vec3> vertices,
				glm::mat4 viewMatrix);

			~Interface();

			GLuint& get_vao();

			void affect_view(glm::mat4 view, glm::vec3 center, glm::vec3 translate_vector);
			void affect_uniforms(glm::vec4 fcolor, glm::vec4 ecolor, int edge_mode);
			
			void draw(Scene &world);
	};
}