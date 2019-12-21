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

	Cube::Cube():m_is_visible(false), m_is_selected(false),m_vertices(8){
		m_face_color = glm::vec4(0, 1, 0, 0);
		m_edge_color = glm::vec4(0, 0, 1, 0);

		m_vertices[0] = (glm::vec3(-0.5, -0.5, -0.5));
        m_vertices[1] = (glm::vec3(0.5, -0.5, -0.5));
        m_vertices[2] = (glm::vec3(-0.5, 0.5, -0.5));
        m_vertices[3] = (glm::vec3(0.5, 0.5, -0.5));
        m_vertices[4] = (glm::vec3(-0.5, -0.5, 0.5));
        m_vertices[5] = (glm::vec3(0.5, -0.5, 0.5));
        m_vertices[6] = (glm::vec3(-0.5, 0.5, 0.5));
        m_vertices[7] = (glm::vec3(0.5, 0.5, 0.5));
	}

	//SET
	void Cube::face_color(glm::vec4 color){
		m_face_color = color;
	}

	void Cube::edge_color(glm::vec4 color){
		m_edge_color = color;
	}

	void Cube::visible(bool state){
		m_is_visible = state;
		if(m_is_visible)
			this->face_color(glm::vec4(0, 1, 0, 1));
		else
			this->face_color(glm::vec4(0, 1, 0, 0));
	}

	void Cube::selected(bool state){
		// std::cout << "switch selection from " << m_is_selected << " to " << state << std::endl;
		m_is_selected = state;
		if(m_is_selected)
			this->edge_color(glm::vec4(1, 0, 0, 1));
		else
			this->edge_color(m_face_color);
		// std::cout << "Edge " << m_edge_color << std::endl;
	}


	//GET
	std::vector<glm::vec3> Cube::vertices() {
		return m_vertices;
	}
	glm::vec4 Cube::face_color() {
		return m_face_color;
	}
	glm::vec4 Cube::edge_color() {
		return m_edge_color;
	}
	bool Cube::is_visible() {
		return m_is_visible;
	}
	bool Cube::is_selected() {
		return m_is_selected;
	}
}
