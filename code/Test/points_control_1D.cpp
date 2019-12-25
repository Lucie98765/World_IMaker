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

#define NB_POINTS 9
#define PIVOT 0.5f
#define NB_PTS_CTRL 3
#define EPSILON 0.001f

using namespace Eigen;

VectorXd LU(const MatrixXd &A, const VectorXd &b){
	PartialPivLU<MatrixXd> lu(A);
	VectorXd x = A*lu.solve(b);
	return x;
}

float phi(int x, int y){
	float res = exp(EPSILON*abs(y-x)*abs(y-x));
	// std::cout << "phi(" << x << ", " << y << ") = " << res << std::endl;
	return res;
}

float g(VectorXd omega, std::vector<int> p_ctrl, int p){
	float res = 0.f;
	for(int i = 0; i < NB_PTS_CTRL; i++){
		res += omega(i)*phi(p, p_ctrl[i]);
	}
	return res;
}


int main(int argc, char** argv){

	std::vector<int> points(NB_POINTS);
	for(int i = 0; i < NB_POINTS; i++)
		points[i] = i;

	std::vector<int> pts_ctrl(NB_PTS_CTRL);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine defaultGenerator(seed);
	

	for(int i = 0; i < NB_PTS_CTRL; i++){
		int pt = defaultGenerator()%NB_POINTS;
		if(pts_ctrl.end() == find(pts_ctrl.begin(), pts_ctrl.end(), pt))
			pts_ctrl[i] = pt;
		else
			i--;
	}

	VectorXd u(NB_PTS_CTRL);
	float mean = 3.0;
	float stdev = 1.5;
	std::normal_distribution<float> normalDistribution(mean,stdev);
	int i = 0;
	while(i < u.size()){
		float value = normalDistribution(defaultGenerator);
		if(0 <= value && value <= 1 && value == value){
			u(i) = value;
			i++;
		}
	}

	MatrixXd phi_mat(NB_PTS_CTRL,NB_PTS_CTRL);
	for(int i = 0; i < phi_mat.cols(); i++)
		for(int j = 0; j < phi_mat.rows(); j++)
			phi_mat(i,j) = phi(pts_ctrl[i],pts_ctrl[j]);

	VectorXd omega = LU(phi_mat, u);

	std::cout << "Points de control : " << std::endl;
	for(int i = 0; i < pts_ctrl.size(); i++){
		std::cout << pts_ctrl[i] << " ";	
	} std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "Valeurs u : " << u.transpose() << std::endl;

	std::cout << std::endl;
 	std::cout << "Phi :\n" << phi_mat << std::endl;
 	
	std::cout << std::endl;
	std::cout << "Omega : " << omega.transpose() << std::endl;
	std::cout << std::endl;

	for(int i = 0; i < NB_POINTS; i++){
		float g_p = g(omega, pts_ctrl, points[i]);
		std::cout << "Valeur du point " << i << " = " << g_p << std::endl;
 		if(g_p >= PIVOT)
			std::cout << "\tAffichage du point " << i << std::endl;
	}


	return 0;
}