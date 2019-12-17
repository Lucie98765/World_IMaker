#pragma once //equivaut au ifndef

#include <glm/glm.hpp>
#include "common.hpp"

#define INVISIBLE 0
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
		void position(glm::vec3 const position);
		void face_color(glm::vec4 const color);
		void edge_color(glm::vec4 const color);
		void state(int state);

		glm::vec3 position() const;
		glm::vec4 face_color() const;
		glm::vec4 edge_color() const;
		int state() const;

};

}