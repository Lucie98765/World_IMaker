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


#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define FORWARD 4
#define BACKWARD 5

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
		Scene(uint w = 1, uint h = 1, uint l = 1);

		void width(uint const w);
		void height(uint const h);
		void length(uint const l);

		uint width() const;		
		uint height() const;		
		uint length() const;
		std::vector<std::vector<std::vector<Cube>>>& cubes();
		TrackballCamera& camera();
		glm::vec3 cursor();		

		void add_cube();
		void delete_cube();
		void extrude_cube();
		void dig_cube();
		void move_cube(glm::vec3 dst);

		void move_cursor(int direction);
		void change_color(glm::vec4 color);

};

}