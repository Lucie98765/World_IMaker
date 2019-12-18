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
		/// \fn face_volor()
		/// \param vec4 const color
		/// \brief Modifie la couleur des faces du cube
		///
		void face_color(glm::vec4 const color);
		///
		/// \fn edge_volor()
		/// \param vec4 const color
		/// \brief Modifie la couleur des aretes du cube
		///
		void edge_color(glm::vec4 const color);
		///
		/// \fn visible()
		/// \param bool const state
		/// \brief Modifie la visibilite du cube
		///
		void visible(bool const state);
		///
		/// \fn selected()
		/// \param bool const state
		/// \brief Modifie l'etat de selection du cube
		///
		void selected(bool const state);

		
		///
		/// \fn face_color() const
		/// \brief Accesseur de la couleur des faces du cube
		/// \return glm::vec4 const m_face_color
		///
		glm::vec4 face_color() const;
		///
		/// \fn edge_color() const
		/// \brief Accesseur de la couleur des aretes du cube
		/// \return glm::vec4 const m_edge_color
		///
		glm::vec4 edge_color() const;
		///
		/// \fn is_visible() const
		/// \brief Accesseur de la visibilite du cube
		/// \return bool const m_is_visible
		///
		bool is_visible() const;
		///
		/// \fn is_selected() const
		/// \brief Accesseur de l'etat de selection du cube
		/// \return bool const m_is_selected
		///
		bool is_selected() const;

};

}