///
/// \file Scene.hpp
/// \brief header classe Scene
/// \author CHIKAR LESBATS
/// \version 0.1
/// \date 19 dec 2019
///
/// Header de la classe Scene
///
///


#pragma once 

#include <glm/glm.hpp>
#include "common.hpp"
#include <vector>

#include "glimac/Cube.hpp"
#include "glimac/TrackballCamera.hpp"


namespace glimac{


class Scene
{

	private:
		uint m_width;
		uint m_height;
		uint m_length;
		std::vector<std::vector<std::vector<Cube>>> m_cubes;
		TrackballCamera m_camera;
		glm::vec3 m_cursor;

	public:
		Scene(uint w = 3, uint h = 3, uint l = 3);

		void width(uint const w);
		void height(uint const h);
		void length(uint const l);
		void camera(TrackballCamera cam);

		uint width() const;		
		uint height() const;		
		uint length() const;
		std::vector<std::vector<std::vector<Cube>>> cubes();
		TrackballCamera camera() const;
		glm::vec3 cursor() const;		

		void add_cube(glm::vec3 pos);
		void delete_cube(glm::vec3 pos);
		void extrude_cube(glm::vec3 pos);
		void dig_cube(glm::vec3 pos);
		void move_cube(glm::vec3 src, glm::vec3 dst);

		void move_cursor(glm::vec3 pos);

};

}