///
/// \file RBF.cpp
/// \brief source de la classe RBF
/// \author CHIKAR LESBATS
/// \version 0.1
/// \date 26 dec 2019
///
/// Code source de la classe RBF
///
///


#include "glimac/RBF.hpp"

VectorXd LU(const MatrixXd &A, const VectorXd &b){
	PartialPivLU<MatrixXd> lu(A);
	VectorXd x = A*lu.solve(b);
	return x;
}

namespace glimac{



	void RBF::build(std::vector<glm::vec3> points, std::vector<glm::vec3> points_ctrl, std::function<float (glm::vec3 x, glm::vec3 y)> func){

		pts_ctrl = points_ctrl;

		//generation values_ctrl
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine defaultGenerator(seed);

		float mean = 3.0;
		float stdev = 1.5;
		std::normal_distribution<float> normalDistribution(mean,stdev);
		int i = 0;
		while(i < values_ctrl.size()){
			float value = normalDistribution(defaultGenerator);
			//avoid wrong values (< -1, > 1 or nan)
			if(-1 <= value && value <= 1 && value == value){
				values_ctrl(i) = value;
				i++;
			}
		}

		//RBF chosen
		phi = func;
	}

	void RBF::build(std::vector<glm::vec3> points, int nb_points_ctrl, std::function<float (glm::vec3 x, glm::vec3 y)> func){

		//generation pts_ctrl
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine defaultGenerator(seed);

		std::vector<int> shuffled_pts(nb_points_ctrl);
		for(int i = 0; i < shuffled_pts.size(); i++) shuffled_pts[i] = i;
		shuffle(shuffled_pts.begin(), shuffled_pts.end(), defaultGenerator);
		
		for(int i = 0; i < nb_points_ctrl; i++)
			pts_ctrl[i] = points[shuffled_pts[i]];

		//generation values_ctrl
		float mean = 3.0;
		float stdev = 1.5;
		std::normal_distribution<float> normalDistribution(mean,stdev);
		int i = 0;
		while(i < values_ctrl.size()){
			float value = normalDistribution(defaultGenerator);
			//avoid wrong values (< -1, > 1 or nan)
			if(-1 <= value && value <= 1 && value == value){
				values_ctrl(i) = value;
				i++;
			}
		}

		//RBF chosen
		phi = func;
	}

	float RBF::g(glm::vec3 point){
		MatrixXd phi_mat(pts_ctrl.size(),pts_ctrl.size());
		for(int i = 0; i < phi_mat.cols(); i++)
			for(int j = 0; j < phi_mat.rows(); j++)
				phi_mat(i,j) = phi(pts_ctrl[i],pts_ctrl[j]);

		//LU solve because phi_mat is symetrical and regular
		VectorXd omega = LU(phi_mat, values_ctrl);

		float res = 0.f;
		for(size_t i = 0; i < pts_ctrl.size(); i++){
			res += omega(i)*phi(point, pts_ctrl[i]);
		}
		return res;
	}

	bool RBF::is_displayable(glm::vec3 point, float pivot, std::function<bool (glm::vec3, float)> predicate){
		return predicate(point, pivot);
	}
}