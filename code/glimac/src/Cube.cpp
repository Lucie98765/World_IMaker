#include <iostream>
#include "glimac/Cube.hpp"
#include <vector>

namespace glimac{

//Constructor(s)
Cube::Cube(glm::vec3 position = glm::vec3(0)): m_state(INVISIBLE){
	m_position = position;
	m_face_color = glm::vec4(0);
	m_edge_color = glm::vec4(0);
}

Cube::Cube():Cube(glm::vec3(0)){}

//Methods
void Cube::position(glm::vec3 const position){
	m_position = position;
}
void Cube::face_color(glm::vec4 const color){
	m_face_color = color;
}

void Cube::edge_color(glm::vec4 const color){
	m_edge_color = color;
}

void Cube::state(int const state){
	m_state = state;
	switch(m_state){
		case VISIBLE: this->face_color(glm::vec4(0, 1, 0, 1));
					  this->edge_color(glm::vec4(0, 1, 0, 1));
					  break;
		case INVISIBLE: this->face_color(glm::vec4(0, 0, 0, 0));
					  	this->edge_color(glm::vec4(0, 0, 0, 0));
					  	break;
		case SELECTED: this->edge_color(glm::vec4(1, 0, 0, 1));
	}
}

glm::vec3 Cube::position() const {
	return m_position;
}
glm::vec4 Cube::face_color() const {
	return m_face_color;
}
glm::vec4 Cube::edge_color() const {
	return m_edge_color;
}
int Cube::state() const {
	return m_state;
}

}
