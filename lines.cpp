#include <iostream>
#include "rotations.h"
#include "Eigen/Geometry"
#include "Eigen/Cholesky"
#include <fstream>
using namespace std;
using Vector2f = Eigen::Vector2f; // 2x1 vector of floats
using Vector4f = Eigen::Vector4f;
using Vector2fVector=std::vector<Eigen::Vector2f, Eigen::aligned_allocator<Eigen::Vector2f> >;
using ContainerType = std::vector<Vector2f, Eigen::aligned_allocator<Vector2f> >;
void drawLine(Vector2fVector& dest,
              const Vector2f& p0,
              const Vector2f& p1,
              float density) {
  Vector2f delta=p1-p0;
  float length=delta.norm();
  int n_points=length*density;
  Vector2f d=delta/n_points;
  for (int i=0; i<n_points; ++i) 
    dest.push_back(p0+d*float(i));
  
}

int main(int argc, char** argv){
	
  ContainerType kd_points;
  for (int i=0; i<11; ++i) {
    Vector2f p0=(Vector2f::Random()-Vector2f(-0.5, -0.5))*50;
    Vector2f p1=(Vector2f::Random()-Vector2f(-0.5, -0.5))*50;
    drawLine(kd_points, p0, p1,10);
  } 
  ofstream file("lines.dat");
	int cnt =0;
	for (auto& elem: kd_points){  
      cnt ++;
      cout<< cnt << " : each element : " << elem << endl;
      file << elem(0) << ' ' << elem(1) << endl;
	}
	
	}
