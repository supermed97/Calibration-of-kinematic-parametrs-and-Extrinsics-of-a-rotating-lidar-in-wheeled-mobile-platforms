#include "Eigen/Geometry"
#include "Eigen/Cholesky"
#include "rotations.h"
#include "simulator.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
using Vector2f = Eigen::Vector2f; // 2x1 vector of floats
using Vec_points= std::vector<Vector2f, Eigen::aligned_allocator<Vector2f> >; // vector of (x,y) points
using Vector4f = Eigen::Vector4f;
using Vector2fVector=std::vector<Eigen::Vector2f, Eigen::aligned_allocator<Eigen::Vector2f> >;
using ContainerType = std::vector<Vector2f, Eigen::aligned_allocator<Vector2f> >;
using namespace std;

int main(int argc, char** argv) {
position  pose;   

/** I USE SPACE_POINT AND TRAJECTORY AS A WAY TO HAVE A VECTOR OF EACH (X,Y) POSITION OF THE ROBOT **/  
Vector2f space_point; 
Vec_points trajectory,ray_points; 
ofstream three_d("45deg.dat");
Vector2f ray_dir;
pose.delta_x=0; pose.delta_y=0; pose.theta=0;  //INITIAL POSE OF ROBOT
float beam_angle = M_PI/5;
ray_dir=create_ray(&pose, beam_angle);
for(int i=1; i< 200;i++){
	space_point(0)=pose.delta_x + (i*ray_dir(0)); space_point(1)=pose.delta_y+(i*ray_dir(1));
	three_d<< space_point(0)<<' ' << space_point(1) << endl;
	}
	
}
