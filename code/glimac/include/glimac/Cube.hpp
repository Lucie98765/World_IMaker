#pragma once //equivaut au ifndef

#include <glm/glm.hpp>
#include "common.hpp"

#define INVISBILE 0
#define VISIBLE 1
#define SELECTED 2

namespace glimac{

class Cube
{
	private:
		glm::vec3 m_position;
		glm::vec4 m_face_color;
		glm::vec4 m_edge_color;
		int m_state;



	public:
		//Constructor(s)
		Cube();
		Cube(glm::vec3 position);

		//Methods
		void set_face_color(int r, int g, int b);
		void set_edge_color(int r, int g, int b);
		void set_state(int state);

};

}