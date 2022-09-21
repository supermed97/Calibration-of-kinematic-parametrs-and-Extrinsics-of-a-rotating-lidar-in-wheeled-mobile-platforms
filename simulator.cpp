#include "Eigen/Geometry"
#include "Eigen/Cholesky"
#include "rotations.h"
#include "simulator.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

float polinomial(float theta, char dir){
 float approx;
 if (theta <= 2 && theta >=-2){
 if(dir =='x'){
  approx = 1 - ( pow(theta,2) )/6  + ( pow(theta,4) )/120 - ( pow(theta,6) )/5040 ;
  }
 else if (dir =='y'){
  approx = theta/2 - ( pow(theta,3) )/24  + ( pow(theta,5) )/720 ;
  }
}
  else {
  if(dir =='x'){
  approx = sin(theta)/theta ;
  }
 else if (dir =='y'){
  approx = (1-cos(theta))/theta;
  }
}
  return approx;}
  
  
 
 
float theta(int tick_r, int tick_l,float k_l, float k_r, float b){
 float theta = (k_l *tick_l) - (k_r * tick_r);
 cout<< "I am IN FUNCTION THETA ! : " << theta << endl ;
 theta = theta/b;
 
 return theta;
  }
  
float  x(int tick_r, int tick_l,float k_l, float k_r, float b,float theta){
 float x =  ( (k_l *tick_l) + (k_r * tick_r) )/2;
 x = x * polinomial(theta,'x');
 return x;
  }
  
float  y( int tick_r,int tick_l,float k_l, float k_r, float b,float theta){
 float y =  ( (k_l *tick_l) + (k_r * tick_r) )/2;
 y = y * polinomial(theta,'y');
 return y;
  }
  
 float delta_s(float r, float omega_r, float omega_l, float T) {
	 float delta_s = (r*omega_r*T)+ (r*omega_l*T);
	 delta_s=delta_s/2;
	 return delta_s;
	 }
float delta_theta(float r, float omega_r, float omega_l, float T,float b) {
	 float delta_th = (r*omega_r*T) - (r*omega_l*T);
	 delta_th=delta_th/b;
	 return delta_th;
	 }	 
	 
std::vector<float> quad_solver(float a, float b, float c){
           std::vector<float> sol;
          float  discriminant, x1, x2;
        discriminant = b*b - 4*a*c;
    
    if (discriminant >= 0) {
        x1 = (-b + sqrt(discriminant)) / (2*a);
        x2 = (-b - sqrt(discriminant)) / (2*a);
        if(x1==x2){ sol.push_back(x1);}
        else{
        sol.push_back(x1); sol.push_back(x2);}
    }
    return sol;
}
