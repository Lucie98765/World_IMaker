///
/// \file Cube.hpp
/// \brief header classe Cube
/// \author CHIKAR LESBATS
/// \version 0.1
/// \date 18 dec 2019
///
/// Header de la classe Cube
///
///


#pragma once 

#include <glm/glm.hpp>
#include "common.hpp"
#include <vector>

namespace glimac{


class Cube
{
	private:		
		///
		/// position des sommets
		///
		std::vector<glm::vec3> m_vertices_position;
        ///
        /// position des sommets, normales aux sommets et coordonnées de texture
        ///
        std::vector<ShapeVertex> m_vertices;
		///
		/// couleur des faces
		///
		glm::vec4 m_face_color;
		///
		/// couleur des aretes
		///
		glm::vec4 m_edge_color;
		///
		/// visibilite
		///
		bool m_is_visible;
		///
		/// etat de selection
		///
		bool m_is_selected;



	public:
		
		///
		/// \fn Cube()
		/// \brief Constructeur de la classe Cube
		/// Initialise un cube au centre du monde en etant invisible
		///
		Cube();
		
		///
		/// \fn face_color()
		/// \param vec4 color
		/// \brief Modifie la couleur des faces du cube
		///
		inline void face_color(glm::vec4 color){m_face_color = color;};
		///
		/// \fn edge_volor()
		/// \param vec4 color
		/// \brief Modifie la couleur des aretes du cube
		///
		inline void edge_color(glm::vec4 color){m_edge_color = color;};
		///
		/// \fn visible()
		/// \param bool state
		/// \brief Modifie la visibilite du cube
		///
		void visible(bool state);
		///
		/// \fn selected()
		/// \param bool state
		/// \brief Modifie l'etat de selection du cube
		///
		void selected(bool state);
		///
		/// \fn vertices()
		/// \brief Accesseur de la position des sommets du
		/// \return std::vector<glm::vec3> m_vertices
		///
		inline std::vector<glm::vec3> vertices() const{return m_vertices_position;};
		///
		/// \fn face_color()
		/// \brief Accesseur de la couleur des faces du cube
		/// \return glm::vec4 m_face_color
		///
		inline glm::vec4 face_color() const{return m_face_color;};
		///
		/// \fn edge_color()
		/// \brief Accesseur de la couleur des aretes du cube
		/// \return glm::vec4 m_edge_color
		///
		inline glm::vec4 edge_color() const{return m_edge_color;};
		///
		/// \fn is_visible()
		/// \brief Accesseur de la visibilite du cube
		/// \return bool m_is_visible
		///
		inline bool is_visible() const{return m_is_visible;};
		///
		/// \fn is_selected()
		/// \brief Accesseur de l'etat de selection du cube
		/// \return bool m_is_selected
		///
		inline bool is_selected() const{return m_is_selected;};

};

}