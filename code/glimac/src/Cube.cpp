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

	Cube::Cube():m_is_visible(false), m_is_selected(false),m_vertices_position(8){
		m_face_color = glm::vec4(0, 1, 0, 0);
		m_edge_color = glm::vec4(1, 0, 0, 0);

		m_vertices_position[0] = (glm::vec3(-0.5, -0.5, -0.5));
        m_vertices_position[1] = (glm::vec3(0.5, -0.5, -0.5));
        m_vertices_position[2] = (glm::vec3(-0.5, 0.5, -0.5));
        m_vertices_position[3] = (glm::vec3(0.5, 0.5, -0.5));
        m_vertices_position[4] = (glm::vec3(-0.5, -0.5, 0.5));
        m_vertices_position[5] = (glm::vec3(0.5, -0.5, 0.5));
        m_vertices_position[6] = (glm::vec3(-0.5, 0.5, 0.5));
        m_vertices_position[7] = (glm::vec3(0.5, 0.5, 0.5));

        for(uint i = 0; i <= 8; ++i) {
            ShapeVertex vertex;

            vertex.texCoords.x = 0;
            vertex.texCoords.y = 0; //Pas de gestion des textures pour l'instant

            vertex.position.x = m_vertices_position[i].x;
            vertex.position.y = m_vertices_position[i].y;
            vertex.position.z = m_vertices_position[i].z;

            vertex.normal = vertex.position;

            m_vertices.push_back(vertex);
        }
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
		m_is_selected = state;
		if(m_is_selected)
			this->edge_color(glm::vec4(1, 0, 0, 1));
		else
			this->edge_color(m_face_color);
	}


	//GET
	std::vector<glm::vec3> Cube::vertices() const {
		return m_vertices_position;
	}
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
