///
/// \file RBF.hpp
/// \brief header pour la classe RBF
/// \author CHIKAR LESBATS
/// \version 0.1
/// \date 26 dec 2019
///
/// Header pour la classe RBF contenant les fonctions mathématiques
///
///


#pragma once 

#include <iostream>
#include <Eigen/Dense>
#include <ctime>
#include <cassert>
#include <cstdlib>

#include <vector>

#include <random>
#include <chrono>
#include <functional>

#include <cmath>

#include <algorithm>

#include <glimac/glm.hpp>


using namespace Eigen;

namespace glimac{
	
	class RBF{
		private:
			std::vector<glm::vec3> pts_ctrl;
			VectorXd values_ctrl;
			std::function<float (glm::vec3 x, glm::vec3 y)> phi;



		public:
			RBF(std::vector<glm::vec3> points, int nb_points_ctrl, std::function<float (glm::vec3 x, glm::vec3 y)> func);

			RBF(std::vector<glm::vec3> points, std::vector<glm::vec3> points_ctrl, std::function<float (glm::vec3 x, glm::vec3 y)> func);


			float g(glm::vec3 point);
			bool is_displayable(glm::vec3 point, float pivot, std::function<bool (glm::vec3, float)> predicate);

	};

}
