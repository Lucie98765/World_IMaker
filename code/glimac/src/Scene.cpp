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


#include <glm/glm.hpp>
#include <vector>

#include "glimac/Scene.hpp"


namespace glimac{

	Scene::Scene(uint w, uint h, uint l):m_width(w),m_height(h),m_length(l),m_camera(),m_cubes(w, std::vector<std::vector<Cube>>(h, std::vector<Cube>(l))),m_cursor(w/2,h/2,l/2){}


	void Scene::width(uint const w){
		m_width = w;
	}
	void Scene::height(uint const h){
		m_height = h;
	}
	void Scene::length(uint const l){
		m_length = l;
	}
	void Scene::camera(TrackballCamera cam){
		m_camera = cam;
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
	TrackballCamera Scene::camera() const{
		return m_camera;
	}
	glm::vec3 Scene::cursor() const{
		return m_cursor;
	}




}