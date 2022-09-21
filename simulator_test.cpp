#include "Eigen/Geometry"
#include "Eigen/Cholesky"
#include "rotations.h"
#include "simulator.h"
#include <vector>
#include <iostream>
#include <fstream>

using Vector2f = Eigen::Vector2f; // 2x1 vector of floats
using Vec_points= std::vector<Vector2f, Eigen::aligned_allocator<Vector2f> >; // vector of (x,y) points

using namespace std;
extern const char ** environ;

int main(int argc, char** argv) {

if (argc<3) {
    cerr << "usage: " << environ[0] << " right_wheel_vel left_wheel_vel simulation_period" << endl ;
    return -1;
  }
float period = 0.5; float end_time = 0; float b = 5; float omega_r;  float omega_l; float sim_time;
 
  omega_r=atof(argv[1]);
  omega_l=atof(argv[2]);
  sim_time=atof(argv[3]);
   
position  pose;   

std::vector<float> sols;

Vector2f space_point;
Vec_points trajectory; 
pose.delta_x=0; pose.delta_y=0; pose.theta=0; 


space_point(0)=pose.delta_x; space_point(1)=pose.delta_y; trajectory.emplace_back(space_point); 
ofstream file0("theta.dat"); ofstream file1("poli.dat"); ofstream three_d("3d.dat");
while(end_time <= sim_time){
	//omega_temp=16/ ( ( pow(polinomial(pose.theta,'x'),2) + pow(polinomial(pose.theta,'y'),2) ) * 4 * pow(end_time,2)   ); 	sols=quad_solver(1,2,(1-omega_temp)); 	cout << "I AM OMEGA1_R : "<< sols[1] << " I AM OMEGA1_R : " << sols[2] << endl; 	omega_r = sols[1];
	pose.delta_x= delta_s(2, omega_r, omega_l, end_time)*polinomial(pose.theta,'x');
	pose.delta_y= delta_s(2, omega_r, omega_l, end_time)*polinomial(pose.theta,'y');
	cout << "OMEGA_R: " << omega_r <<" OMEGA_L : " << omega_l <<endl;
	pose.theta= delta_theta(2, omega_r , omega_l, end_time,b); file0 << end_time << ' ' << pose.theta << endl; file1 << polinomial(pose.theta,'x') << ' ' << polinomial(pose.theta,'y') << endl; three_d<< end_time <<' ' << pose.delta_x <<  ' '<< pose.delta_y << endl;
	space_point(0)=pose.delta_x; space_point(1)=pose.delta_y;
	trajectory.emplace_back(space_point); 
	end_time+=period;
	cout << "time:" << end_time <<"s" <<endl;
	}
	file0.close();
 cout<< " ______________________ " << endl;
     int cnt=0;
     
     ofstream file("data.dat");
    file << "#x y" << endl;
    for (auto& elem: trajectory){  // read as "for (v in kd_points){ ....... }" v is a reference to each element, thisway we avoid copying each element in memory
    cnt ++;
      cout<< cnt << ": each element : " << elem << endl;
     file << elem(0) << ' ' << elem(1) << endl; }
 
    file.close();

  
  

  
  
}


