#include <iostream>
#include "glimac/Cube.hpp"
#include <vector>

namespace glimac{

//Constructor(s)
Cube::Cube():m_position(3, 0), m_state(0), m_face_color(4, 0), m_edge_color(4, 0) {
}

Cube::Cube(glm::vec3 position): m_state(0), m_face_color(4, 0), m_edge_color(4, 0) {
	m_position = position;
}


//Methods
void Cube::set_face_color(float r, float g, float b, float a){
	m_face_color = glm::vec3(r, g, b, a);
}

void Cube::set_edge_color(float r, float g, float b, float a){
	m_edge_color = glm::vec3(r, g, b, a);
}

void Cube::set_state(int state){
	m_state = state; //Trouver un moyen de dire 0 = invisible, 1 = visible, 2 = sélectionné
}

}
