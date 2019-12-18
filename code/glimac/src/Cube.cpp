///
/// \file Cube.cpp
/// \brief source classe Cube
/// \author CHIKAR LESBATS
/// \version 0.1
/// \date 18 dec 2019
///
/// Code source de la classe Cube
///
///

#include <iostream>
#include "glimac/Cube.hpp"
#include <vector>

namespace glimac{

	Cube::Cube():m_is_visible(false), m_is_selected(false){
		m_face_color = glm::vec4(0, 1, 0, 1);
		m_edge_color = glm::vec4(1, 0, 0, 1);
	}

	//SET
	void Cube::face_color(glm::vec4 const color){
		m_face_color = color;
	}

	void Cube::edge_color(glm::vec4 const color){
		m_edge_color = color;
	}

	void Cube::visible(bool const state){
		m_is_visible = state;
	}

	void Cube::selected(bool const state){
		m_is_selected = state;
		if(m_is_selected)
			this->edge_color(glm::vec4(1, 0, 0, 1));
		else
			this->edge_color(glm::vec4(0, 1, 0, 1));
	}


	//GET
	glm::vec4 Cube::face_color() const {
		return m_face_color;
	}
	glm::vec4 Cube::edge_color() const {
		return m_edge_color;
	}
	bool Cube::is_visible() const {
		return m_is_visible;
	}
	bool Cube::is_selected() const {
		return m_is_selected;
	}
}
