///
/// \file Scene.cpp
/// \brief source classe Scene
/// \author CHIKAR LESBATS
/// \version 0.1
/// \date 19 dec 2019
///
/// Code source de la classe Scene
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
		m_cubes.resize(w);
		m_width = w;
	}
	void Scene::height(uint const h){
		for(uint i = 0; i < m_width; i++)
			m_cubes[i].resize(h);
		m_height = h;
	}
	void Scene::length(uint const l){
		for(uint i = 0; i < m_width; i++)
			for(uint j = 0; j < m_height; j++){
				m_cubes[i][j].resize(l);
			}
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
	glm::vec3 Scene::cursor()const{
		return m_cursor;
	}

	void Scene::add_cube(){
        if (m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].is_visible()){
            std::cerr<<"\tWARNING: This cube already exists."<< std::endl;
        } else {
            m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].visible(true);
        }
	}

	void Scene::delete_cube(){
		if (m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].is_visible()){
            m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].visible(false);
        } else {
            std::cerr<< "\tWARNING: There is no cube here to delete."<<std::endl;
        }
	}


	void Scene::extrude_cube(){
		if(!m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].is_visible()){
			std::cerr << "\tWARNING: Can't extrude nothing." << std::endl;
			return;
		}
		float current_x, current_y, current_z;
		current_x = m_cursor[0];
		current_y = m_cursor[1];
		current_z = m_cursor[2];
		while(m_cubes[current_x][current_y][current_z].is_visible()){
			if(current_y == m_height-1){
				std::cerr << "\tWARNING: Can't extrude more than max." << std::endl;
				return;
			}
			current_y++;
		}
		m_cubes[current_x][current_y][current_z].visible(true);
	}

	void Scene::dig_cube(){
		if(!m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].is_visible()){
			std::cerr << "\tWARNING: Can't dig nothing." << std::endl;
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
		            (m_cubes[current_x][current_y][current_z]).selected(false);
		            m_cubes[current_x - 1][current_y][current_z].selected(true);
		            m_cursor = glm::vec3 (current_x-1, current_y, current_z);
		        }
		        else{
		        	std::cerr << "\tWARNING: Can't move farther." << std::endl;
		        }
		        break;
			case RIGHT :
				if (m_cursor[0] < m_width-1){		            
                    m_cubes[current_x][current_y][current_z].selected(false);
                    m_cubes[current_x + 1][current_y][current_z].selected(true);
                    m_cursor = glm::vec3 (current_x+1, current_y, current_z);
                }
                else{
                	std::cerr << "\tWARNING: Can't move farther." << std::endl;
                }
				break;
			case UP :
                if (m_cursor[1] < m_height-1){		            
                    m_cubes[current_x][current_y][current_z].selected(false);
                    m_cubes[current_x][current_y+1][current_z].selected(true);
                    m_cursor = glm::vec3 (current_x, current_y+1, current_z);
                }
                else{
                	std::cerr << "\tWARNING: Can't move farther." << std::endl;
                }
				break;
			case DOWN :
                if (m_cursor[1] > 0){		            
                    m_cubes[current_x][current_y][current_z].selected(false);
                    m_cubes[current_x][current_y-1][current_z].selected(true);
                    m_cursor = glm::vec3 (current_x, current_y-1, current_z);
                }
                else{
                	std::cerr << "\tWARNING: Can't move farther." << std::endl;
                }
				break;
			case FORWARD :
                if (m_cursor[2] < m_length-1){		            
                    m_cubes[current_x][current_y][current_z].selected(false);
                    m_cubes[current_x][current_y][current_z+1].selected(true);
                    m_cursor = glm::vec3 (current_x, current_y, current_z+1);
                }
                else{
                	std::cerr << "\tWARNING: Can't move farther." << std::endl;
                }
				break;
			case BACKWARD :
                if (m_cursor[2] > 0){
                    m_cubes[current_x][current_y][current_z].selected(false);
                    m_cubes[current_x][current_y][current_z-1].selected(true);
                    m_cursor = glm::vec3 (current_x, current_y, current_z-1);
                }
                else{
                	std::cout << "\tWARNING: Can't move farther." << std::endl;
                }
				break;
			default: break;
		}
	}

	void Scene::change_color(glm::vec4 color){
		if(m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].is_visible())
			m_cubes[m_cursor[0]][m_cursor[1]][m_cursor[2]].face_color(color);
		else
            std::cerr << "\tWARNING: You should first create this cube before changing its color." << std::endl;
	}


	void Scene::save(){
		std::cout << "\nPlease enter saving file name (relative or absolute path)" << std::endl;
	    std::string saving_path;
	    std::cin >> saving_path;
	    std::ofstream savingFile;

	    if(saving_path[0] == '/')
	        savingFile = std::ofstream(saving_path);
	    else
	        savingFile = std::ofstream("/home/louisa/IMAC2/POO/World_IMaker/code/savings/"+saving_path);

	    savingFile << m_width << "\n";
	    savingFile << m_height << "\n";
	    savingFile << m_length << "\n";

	    int nb_cubes = 0;
	    std::vector<std::pair<glm::vec3, std::string>> cubes;
	    for(uint i = 0; i < m_width; i++){
	        for(uint j = 0; j < m_height; j++){
	            for(uint k = 0; k < m_length; k++){
	                if(m_cubes[i][j][k].is_visible()){
	                    nb_cubes++;
	                    std::string color;
	                    if(m_cubes[i][j][k].face_color() == glm::vec4(1,0,0,1))
	                        color = "R";
	                    if(m_cubes[i][j][k].face_color() == glm::vec4(0,1,0,1))
	                        color = "G";
	                    if(m_cubes[i][j][k].face_color() == glm::vec4(1,1,0,1))
	                        color = "Y";
	                    if(m_cubes[i][j][k].face_color() == glm::vec4(1,0,1,1))
	                        color = "M";
	                    if(m_cubes[i][j][k].face_color() == glm::vec4(0,1,1,1))
	                        color = "C";

	                    cubes.push_back(std::pair<glm::vec3,std::string>(glm::vec3(i,j,k), color));
	                }
	            }
	        }
	    }

	    savingFile << nb_cubes << "\n";

	    for (const auto& [coord, color]: cubes) 
	        savingFile << coord.x << " " << coord.y << " " << coord.z << " "<< color << "\n";
	    savingFile.close();
	}


	bool Scene::load(){
		std::cout << "\nPlease select a saving file" << std::endl;
	    std::string saved_path;
	    std::cin >> saved_path;

	    std::ifstream savedFile;
	    if(saved_path[0] == '/'){
	        savedFile = std::ifstream(saved_path);
	        try{
		        if(!savedFile.is_open())
	            	throw std::string("Couldn't open saving file");
	        }
	        catch(const std::string &err){
		    	std::cerr << "io error : " << err << std::endl;
		    	return false;
		    }
	    }
	    else{
	        savedFile = std::ifstream("/home/louisa/IMAC2/POO/World_IMaker/code/savings/"+saved_path);
	        try{
		        if(!savedFile.is_open())
	            	throw std::string("Couldn't open saving file");
	        }
	        catch(const std::string &err){
		    	std::cerr << "io error : " << err << std::endl;
		    	return false;
		    }
	    }

	    std::string w, h, l, nb_cubes, cube;

	    std::getline(savedFile, w);
	    std::getline(savedFile, h);
	    std::getline(savedFile, l);
	    std::getline(savedFile, nb_cubes);

	    this->width(std::stoi(w));
	    this->height(std::stoi(h));
	    this->length(std::stoi(l));


	    m_cursor = glm::vec3(m_width/2, m_height/2, m_length/2);

	    if(0 < std::stoi(nb_cubes)){
	        int i,j,k;
	        for(; std::getline(savedFile, cube); i++){
	            std::stringstream ss(cube);
	            std::string token;
	            while(std::getline(ss, token, ' ')){
	                i = std::stoi(token);
	                std::getline(ss, token, ' ');
	                
	                j = std::stoi(token);
	                std::getline(ss, token, ' ');
	                
	                k = std::stoi(token);
	                std::getline(ss, token, ' ');

	                m_cubes[i][j][k].visible(true);
	                if(0 == token.compare("R"))
	                    m_cubes[i][j][k].face_color(glm::vec4(1,0,0,1));
	                else if(0 == token.compare("G"))
	                    m_cubes[i][j][k].face_color(glm::vec4(0,1,0,1));
	                else if(0 == token.compare("Y"))
	                    m_cubes[i][j][k].face_color(glm::vec4(1,1,0,1));
	                else if(0 == token.compare("M"))
	                    m_cubes[i][j][k].face_color(glm::vec4(1,0,1,1));
	                else if(0 == token.compare("C"))
	                    m_cubes[i][j][k].face_color(glm::vec4(0,1,1,1));
	            }
	        }
	    }
	    savedFile.close();
	    return true;
	}


	bool Scene::generate(){
		std::cout << "\nPlease select a config file" << std::endl;
	    std::string config;
	    std::cin >> config;

		std::ifstream confFile("/home/louisa/IMAC2/POO/World_IMaker/code/config/"+config);
	    try{
		    if(!confFile.is_open())
		        throw std::string("Couldn't open config file");
	    }
	    catch(const std::string &err){
	    	std::cerr << "io error : " << err << std::endl;
	    	return false;
	    }

	    std::string w, h, l, phi, display, nb_pts_ctrl;

	    std::getline(confFile, w); 
	    std::getline(confFile, h); 
	    std::getline(confFile, l); 
	    std::getline(confFile, phi);
	    std::getline(confFile, display);
	    std::getline(confFile, nb_pts_ctrl);

	    //init scene
	    this->width(std::stoi(w));
	    this->height(std::stoi(h));
	    this->length(std::stoi(l));

	    m_cursor = glm::vec3(m_width/2, m_height/2, m_length/2);

	    //affect phi func
	    std::function<float (glm::vec3 x, glm::vec3 y)> func;

	    std::function<float (glm::vec3 x, glm::vec3 y)> exp_phi = [](glm::vec3 x, glm::vec3 y){
	        return exp(0.01*abs(glm::distance(x,y))*abs(glm::distance(x,y)));};
	    std::function<float (glm::vec3 x, glm::vec3 y)> lin_phi = [](glm::vec3 x, glm::vec3 y){
	        return 0.01*abs(glm::distance(x,y))*abs(glm::distance(x,y));};
	    std::function<float (glm::vec3 x, glm::vec3 y)> sqrt_phi = [](glm::vec3 x, glm::vec3 y){
	        return sqrt(1+pow(0.01*abs(glm::distance(x,y))*abs(glm::distance(x,y)),2));};
	    std::function<float (glm::vec3 x, glm::vec3 y)> rat_phi = [](glm::vec3 x, glm::vec3 y){
	        return 1/(1+pow(0.01*abs(glm::distance(x,y))*abs(glm::distance(x,y)),2));};

	    if(0 == phi.compare("exp")) func = exp_phi;
	    if(0 == phi.compare("lin")) func = lin_phi;
	    if(0 == phi.compare("sqrt")) func = sqrt_phi;
	    if(0 == phi.compare("rat")) func = rat_phi;

	    // Cube matrix
	    std::vector<glm::vec3> cube_matrix(m_width*m_height*m_length);
	    for(uint i = 0; i < m_width; i++)
	        for(uint j = 0; j < m_height; j++)
	            for(uint k = 0; k < m_length; k++)
	                cube_matrix[i*k*k+j*k+k] = glm::vec3(i,j,k);

	    // init RBF
	    RBF rbf(std::stoi(nb_pts_ctrl));
	    int i = 0;
	    std::string pt_ctrl;
	    std::vector<glm::vec3> list_pts_ctrl(stoi(nb_pts_ctrl));
	    int x, y, z;


	    //Case control points given
	    for(; std::getline(confFile, pt_ctrl); i++){
	        std::stringstream ss(pt_ctrl);
	        std::string token;
	        while(std::getline(ss, token, ' ')){
	            x = std::stoi(token);
	            std::getline(ss, token, ' ');
	            
	            y = std::stoi(token);
	            std::getline(ss, token, ' ');
	            
	            z = std::stoi(token);

	            list_pts_ctrl[i] = (glm::vec3(x,y,z));  
	        }


	    }
	    if(0 < i)
	        rbf.build(cube_matrix, list_pts_ctrl, func);

	    //Case nb control points given
	    else
	        rbf.build(cube_matrix, std::stoi(nb_pts_ctrl), func);
	    
	    //Calculation interpolated values
	    std::vector<float> g_p(cube_matrix.size());
	    for(size_t i = 0; i < g_p.size(); i++)
	        g_p[i] = rbf.g(cube_matrix[i]);

	    //Affect display condition
	    std::function<bool (glm::vec3, float)> predicate;
	    float pivot;

	    if(0 == display.compare("moy")){
	        predicate = [rbf](glm::vec3 p, float pivot) mutable {
	                            return 0.001 >= abs(rbf.g(p) - pivot);
	                        };
	        pivot = std::accumulate(g_p.begin(), g_p.end(), 0.f)/g_p.size();
	    }

	    else{
	        predicate = [rbf](glm::vec3 p, float pivot) mutable {
	                    return rbf.g(p) >= pivot;
	        };
	        pivot = stof(display);
	    }

	    //Update visibility of cubes
	    for(uint i = 0; i < m_width; i++){
	        for(uint j = 0; j < m_height; j++){
	            for(uint k = 0; k < m_length; k++){
	                if(i == m_width/2 && j == m_height/2 && k == m_length/2)
	                    m_cubes[i][j][k].selected(true);
	                else
	                    m_cubes[i][j][k].selected(false);
	                m_cubes[i][j][k].visible(
	                    rbf.is_displayable(cube_matrix[i*k*j+j*k+k], 
	                        pivot, predicate));
	            }
	        }
	    }

	    return true;
	}
}