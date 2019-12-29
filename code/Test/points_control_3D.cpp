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

#define NB_POINTS 27
#define NB_PTS_CTRL 9
#define EPSILON 0.001f

using namespace Eigen;

VectorXd LU(const MatrixXd &A, const VectorXd &b){
	PartialPivLU<MatrixXd> lu(A);
	VectorXd x = A*lu.solve(b);
	return x;
}

float phi(glm::vec3 x, glm::vec3 y){
	float res = exp(EPSILON*abs(glm::distance(x,y))*abs(glm::distance(x,y)));
	// std::cout << "phi(" << x << ", " << y << ") = " << res << std::endl;
	return res;
}

float g(VectorXd omega, std::vector<glm::vec3> p_ctrl, glm::vec3 p){
	float res = 0.f;
	for(int i = 0; i < NB_PTS_CTRL; i++){
		res += omega(i)*phi(p, p_ctrl[i]);
	}
	return res;
}


int main(int argc, char** argv){

	std::vector<glm::vec3> points(NB_POINTS);
	int dim = pow(NB_POINTS, 1./3.);
	for(int i = 0; i < dim; i++)
		for(int j = 0; j < dim; j++)
			for(int k = 0; k < dim; k++)
				points[i*k*k+j*k+k] = glm::vec3(i, j, k);

	std::cout << "ok points ?" << std::endl;

	std::vector<glm::vec3> pts_ctrl(NB_PTS_CTRL);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine defaultGenerator(seed);

	std::vector<int> shuffled_pts(NB_PTS_CTRL);
	for(int i = 0; i < shuffled_pts.size(); i++) shuffled_pts[i] = i;
	shuffle(shuffled_pts.begin(), shuffled_pts.end(), defaultGenerator);
	
	for(int i = 0; i < NB_PTS_CTRL; i++){
		std::cout << "\tgeneration " << i << " ==> point["<< shuffled_pts[i] << "]" << std::endl;
		pts_ctrl[i] = points[shuffled_pts[i]];
	}

	std::cout << "ok points ctrl?" << std::endl;

	std::cout << "Points de control : " << std::endl;
	for(int i = 0; i < pts_ctrl.size(); i++){
		std::cout << pts_ctrl[i] << " ";	
	} std::cout << std::endl;

	VectorXd u(NB_PTS_CTRL);
	float mean = 1.0;
	float stdev = 0.5;
	std::normal_distribution<float> normalDistribution(mean,stdev);
	int i = 0;
	while(i < u.size()){
		float value = normalDistribution(defaultGenerator);
		if(-5 <= value && value <= 5 && value == value){
			u(i) = value;
			i++;
		}
	}

	std::cout << std::endl;
	std::cout << "Valeurs u : " << u.transpose() << std::endl;

	MatrixXd phi_mat(NB_PTS_CTRL,NB_PTS_CTRL);
	for(int i = 0; i < phi_mat.cols(); i++)
		for(int j = 0; j < phi_mat.rows(); j++)
			phi_mat(i,j) = phi(pts_ctrl[i],pts_ctrl[j]);

	std::cout << std::endl;
 	std::cout << "Phi :\n" << phi_mat << std::endl;

	VectorXd omega = LU(phi_mat, u);
 	
	std::cout << std::endl;
	std::cout << "Omega : " << omega.transpose() << std::endl;
	std::cout << std::endl;

	std::vector<float> g_p(NB_POINTS);
	for(int i = 0; i < NB_POINTS; i++){
		g_p[i] = g(omega, pts_ctrl, points[i]);
		std::cout << "Valeur du point " << i << " = " << g_p[i] << std::endl;
	}

	float pivot = std::accumulate( g_p.begin(), g_p.end(), 0.f )/ g_p.size();
	std::cout << "Valeur moyenne = " << pivot << std::endl;
 	for(int i = 0; i < NB_POINTS; i++){
		// if(EPSILON >= abs(g_p[i]-pivot))
		// 		std::cout << "\tAffichage du point " << i << std::endl;
		if(0 < g_p[i])
			std::cout << "\tAffichage du point " << i << std::endl;
	}


	return 0;
}