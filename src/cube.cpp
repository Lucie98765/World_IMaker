#include <iostream>
#include "cube.hpp"


//Constructor(s)
Cube::Cube(glm::vec3 position, uint indice){
	m_position = position;
	m_indice = indice; 
	m_face_color = glm::vec3(0, 0, 0);
	m_edge_color = glm::vec3(0, 0, 0);;
	m_state = 0;
}


//Methods
void Cube::set_face_color(int r, int g, int b){
	m_face_color = glm::vec3(r, g, b);
}

void Cube::set_edge_color(int r, int g, int b){
	m_edge_color = glm::vec3(r, g, b);
}

void Cube::set_state(int state){
	m_state = state; //Trouver un moyen de dire 0 = invisible, 1 = visible, 2 = sélectionné
}
