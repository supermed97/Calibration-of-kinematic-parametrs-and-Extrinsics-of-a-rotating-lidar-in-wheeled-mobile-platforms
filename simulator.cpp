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

using namespace std;
using Vector2f=Eigen::Vector2f;
using Vector2fVector=std::vector<Eigen::Vector2f, Eigen::aligned_allocator<Eigen::Vector2f> >;

void write_to_file(string filename, string text){
	ofstream file(filename);
	file<< text;
	file.close();
	}

float polinomial(float theta, char dir){
 float approx;
 if (theta <= 1 && theta >=-1){
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

void map_to_file(string filename, Vector2fVector& vec_of_points){  // write 
	ofstream file(filename);
    int riga =0;
    for (auto& elem: vec_of_points){  
    riga ++;
     file << elem(0) << ' ' << elem(1) << endl;
					if(filename=="rays.dat" && riga %2==0){
								file << endl;  }
		      }
     
 file.close();

	}

Vector2f create_ray(position *Pose_robot, float ray_angle){
  float cartesian_direction = tan(ray_angle); // 
	
  Eigen::Vector2f vector_direction,P_robot;        															  //cout << "______________" << endl;  cout << "I AM DELTA : " << delta << endl;
  vector_direction(0)=1-(Pose_robot->delta_x); 											             // or 1-( (*Pose_robot).delta_x );
  vector_direction(1)= cartesian_direction*(vector_direction(0));
  P_robot(0)=Pose_robot->delta_x; P_robot(1)=Pose_robot->delta_y; //
  
  float length=vector_direction.norm();    cout << "______________" << endl;  cout << "I AM NORM : " << length << endl;
  int n_points=length*15;  
  Vector2f ray_dir=vector_direction/n_points;  
  
	  return ray_dir;
		}
Vector2f cast_ray(position *Pose_robot, Vector2f ray_dir, Vector2fVector& ray_points, string filename, Vector2fVector intersections){	
	Eigen::Vector2f P_robot, point_intersect;     // robots pose and point of intersection     															  //cout << "______________" << endl;  cout << "I AM DELTA : " << delta << endl;
    float range;   // distance between robots pose and pointS of intersect
    std::vector<float> ranges; // a ray starting from the robots pose can intersect with all the lines so this vector stores all their ranges
    P_robot(0)=Pose_robot->delta_x; P_robot(1)=Pose_robot->delta_y; 
	ray_points.push_back(P_robot);
	for (auto& elem:intersections){ // for each vector (intersection scalars) in intersections
		point_intersect=P_robot+ray_dir*elem(1); // calculate the point of the intersection 
		cout<<"SCALARS INTERSECT -> "<<elem << " POINT INTERSECT : ---> " << point_intersect << endl;
		range = norm2d(P_robot,point_intersect); // calculate the norm or distance or range
		ranges.push_back(range); // store each range in ranges
		}
	float min_range= *min_element(ranges.begin(), ranges.end()); // take minimum range in ranges
	for (auto& elem:intersections){
		if( norm2d(P_robot,P_robot+ray_dir*elem(1)) == min_range){
			point_intersect == P_robot+ray_dir*elem(1); }
			
		}
	float const minimum_range = 55;	
	float const max_range = 70;
	if (norm2d(P_robot,point_intersect)<= max_range && norm2d(P_robot,point_intersect)>= minimum_range){
		ray_points.push_back(point_intersect);    }
      map_to_file(filename, ray_points);
       string seperator = "\n";
      // write_to_file(filename, seperator); 
       return point_intersect;
       
	}	

	
	
	
void drawLine(Vector2fVector& dest, const Vector2f& p0, const Vector2f& p1,float density, lines_elements *line_info) { 
		
																							cout << "I AM p0 : " << p0 << endl; cout << "______________" << endl; cout << "I AM p1 : " << p1 << endl; 
  Vector2f delta=p1-p0; 																	cout << "______________" << endl;  cout << "I AM DELTA : " << delta << endl;
  float length=delta.norm();   																 cout << "______________" << endl;  cout << "I AM NORM : " << length << endl;
  int n_points=length*density;  
  Vector2f d=delta/n_points;  
  line_info->line_p0 = p0;
  line_info->line_dir = delta;       														cout << "______________" << endl;  cout << "I AM THE DIRECTION : " << d << endl;
  for (int i=0; i<n_points; ++i) 
    dest.push_back(p0+d*float(i));
  
}
	

Vector2f calc_intersection(Vector2f P0, Vector2f line_dir, position *Pose_robot,  Vector2f ray_dir ){
	 Eigen::Matrix2f A;
   Eigen::Vector2f b;
   A << line_dir(0),-ray_dir(0), 
        line_dir(1),-ray_dir(1);
   
   b << Pose_robot->delta_x -P0(0), Pose_robot->delta_y -P0(1);
   
   std::cout << "Here is the matrix A:\n" << A << std::endl;
   std::cout << "Here is the vector b:\n" << b << std::endl;
   Eigen::Vector2f s;
   if(A.determinant()==0){s(0)=0; s(1)=0;}
   else{
   s = A.colPivHouseholderQr().solve(b);}
  std::cout << "The intersection scalars are :\n" << s << std::endl;	
   
   return s;
	
	}


float norm2d(Vector2f Start, Vector2f End){
	  float range= pow(Start(0)-End(0) ,2) + pow(Start(1)-End(1),2);
	  range = pow(range,0.5);
	  return range; 
	}


















