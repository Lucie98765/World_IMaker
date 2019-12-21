///
/// \file Scene.hpp
/// \brief header classe Scene
/// \author CHIKAR LESBATS
/// \version 0.1
/// \date 19 dec 2019
///
/// Code sourve de la classe Scene
///
///


#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#include "glimac/Scene.hpp"

namespace glimac{

	Scene::Scene(uint w, uint h, uint l):m_width(w),m_height(h),m_length(l),m_camera(),m_cubes(w, std::vector<std::vector<Cube>>(h, std::vector<Cube>(l))),m_cursor(w/2,h/2,l/2){
		m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].selected(true);
	}


	void Scene::width(uint const w){
		m_width = w;
	}
	void Scene::height(uint const h){
		m_height = h;
	}
	void Scene::length(uint const l){
		m_length = l;
	}


	uint Scene::width() const{
		return m_width;
	}
	uint Scene::height() const{
		return m_height;
	}
	uint Scene::length() const{
		return m_length;
	}
	std::vector<std::vector<std::vector<Cube>>>& Scene::cubes(){
		return m_cubes;
	}
	TrackballCamera& Scene::camera(){
		return m_camera;
	}
	glm::vec3 Scene::cursor(){
		return m_cursor;
	}

	void Scene::add_cube(){
        if (m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].is_visible()){
            std::cout<<"This cube already exists."<< std::endl;
        } else {
            m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].visible(true);
        }
	}

	void Scene::delete_cube(){
		if (m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].is_visible()){
            m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].visible(false);
        } else {
            std::cout<< "There is no cube here to delete."<<std::endl;
        }
	}


	void Scene::extrude_cube(){
		if(!m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].is_visible()){
			std::cout << "Can't extrude nothing." << std::endl;
			return;
		}
		float current_x, current_y, current_z;
		current_x = m_cursor[0];
		current_y = m_cursor[1];
		current_z = m_cursor[2];
		while(m_cubes[current_x][current_y][current_z].is_visible()){
			if(current_y == m_height-1){
				std::cout << "Can't extrude more than max." << std::endl;
				return;
			}
			current_y++;
		}
		m_cubes[current_x][current_y][current_z].visible(true);
	}

	void Scene::dig_cube(){
		if(!m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].is_visible()){
			std::cout << "Can't dig nothing." << std::endl;
			return;
		}
		float current_x, current_y, current_z;
		current_x = m_cursor[0];
		current_y = m_height-1;;
		current_z = m_cursor[2];

		while(!m_cubes[current_x][current_y][current_z].is_visible()){
			current_y--;
		}
		m_cubes[current_x][current_y][current_z].visible(false);
	}

	void Scene::move_cursor(int direction){
		float current_x, current_y, current_z;
		current_x = m_cursor[0];
        current_y = m_cursor[1];
        current_z = m_cursor[2];


		switch(direction){
			case LEFT :
				if (m_cursor[0] > 0){
		            // std::cout<< "left" << m_cursor << std::endl;
		            
		            (m_cubes[current_x][current_y][current_z]).selected(false);
		            m_cubes[current_x - 1][current_y][current_z].selected(true);
		            m_cursor = glm::vec3 (current_x-1, current_y, current_z);
		        }
		        else{
		        	std::cout << "Can't move farther." << std::endl;
		        }
		        break;
			case RIGHT :
				if (m_cursor[0] < m_width-1){
                    // std::cout<< "right"<< m_cursor << std::endl;
		            
                    m_cubes[current_x][current_y][current_z].selected(false);
                    m_cubes[current_x + 1][current_y][current_z].selected(true);
                    m_cursor = glm::vec3 (current_x+1, current_y, current_z);
                }
                else{
                	std::cout << "Can't move farther." << std::endl;
                }
				break;
			case UP :
                if (m_cursor[1] < m_height-1){
                    // std::cout<< "up"<< m_cursor << std::endl; 
		            
                    m_cubes[current_x][current_y][current_z].selected(false);
                    m_cubes[current_x][current_y+1][current_z].selected(true);
                    m_cursor = glm::vec3 (current_x, current_y+1, current_z);
                }
                else{
                	std::cout << "Can't move farther." << std::endl;
                }
				break;
			case DOWN :
                if (m_cursor[1] > 0){
                    // std::cout<< "down"<< m_cursor << std::endl;
		            
                    m_cubes[current_x][current_y][current_z].selected(false);
                    m_cubes[current_x][current_y-1][current_z].selected(true);
                    m_cursor = glm::vec3 (current_x, current_y-1, current_z);
                }
                else{
                	std::cout << "Can't move farther." << std::endl;
                }
				break;
			case FORWARD :
                if (m_cursor[2] < m_length-1){
                    // std::cout<< "far "<< m_cursor << std::endl; 
		            
                    m_cubes[current_x][current_y][current_z].selected(false);
                    m_cubes[current_x][current_y][current_z+1].selected(true);
                    m_cursor = glm::vec3 (current_x, current_y, current_z+1);
                }
                else{
                	std::cout << "Can't move farther." << std::endl;
                }
				break;
			case BACKWARD :
                if (m_cursor[2] > 0){
                    // std::cout<< "near "<< m_cursor << std::endl;
                    m_cubes[current_x][current_y][current_z].selected(false);
                    m_cubes[current_x][current_y][current_z-1].selected(true);
                    m_cursor = glm::vec3 (current_x, current_y, current_z-1);
                }
                else{
                	std::cout << "Can't move farther." << std::endl;
                }
				break;
			default : //error
				break;
		}
	}

	void Scene::change_color(glm::vec4 color){
		if(m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].is_visible())
			m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].face_color(color);
		else
            std::cout << "You should first create this cube before changing its color." << std::endl;
	}

}