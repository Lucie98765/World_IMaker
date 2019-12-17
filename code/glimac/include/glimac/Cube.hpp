#pragma once //equivaut au ifndef

#include <glm/glm.hpp>
#include "common.hpp"


namespace glimac{

class Cube
{
	private:
		glm::vec3 m_position;
		uint m_indice; 
		glm::vec3 m_face_color;
		glm::vec3 m_edge_color;
		int m_state;



	public:
		//Constructor(s)
		Cube(glm::vec3 position, uint indice);

		//Methods
		void set_face_color(int r, int g, int b);
		void set_edge_color(int r, int g, int b);
		void set_state(int state);

};

}