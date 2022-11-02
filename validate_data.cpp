#include "eigen_micp_2d_utils.h"
#include "rotations.h"
#include <iostream>
#include <fstream>
#include <limits>
#include "eigen_micp_2d.h"
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
extern const char ** environ;

void print(std::vector<auto> vector){
	for (auto& elem:vector){
		cout << elem << endl;
	}
	//cout <<endl;
}

int main(int argc, char** argv) {
  /**____________________ PROF SECTOR ______________________________________**/
  using ContainerType=Vector2fVector;
   
  cout << "set size ratio -1" << endl;
  cout << "set term x11 0" << endl;
  cout << "set size ratio -1" << endl;
  cout << "set term x11 1" << endl;  
  int tot_count=0;
  int neg_cnt=0;
  /***_______________________________________________________ ***/
    
  /****FILL VECTORS FOR MICP FROM MY SIMULATOR *****/
  double time_stamp;
  float  x,y,theta, x_endpoint, y_endpoint;   // VARIABLES TO STORE DATA OF EACH LINE TEMPORARILY
  float beam_angle, range;       // VARIABLES TO STORE DATA OF EACH LINE TEMPORARILY
  string line;                  // VARIABLE TO READ LINE
  ifstream input_File;         // OBJECT TO OPEN FILE AND ACCESS IT
  input_File.open("micp_file.dat"); // USE OBJECT TO OPEN FILE
    
  if(input_File.fail()) { 
    cout << "error COULDNT OPEN FILE " << endl; 
    return 1; // no point continuing if the file didn't open...
  } 
    
  std::vector<double> stamps;      // work vector 1
  std::vector<float> beam_angles; // work vector 2    
  std::vector<float> ranges;      // work vector 3
  std::vector<float> x_;      // control vector 1
  std::vector<float> y_;      // control vector 2
  std::vector<float> theta_;      // control vector 3
  
  //std::vector<Eigen::Vector2f, Eigen::aligned_allocator<Eigen::Vector2f> > endpoints;
  ofstream os("endpoints_rads");
  while (std::getline(input_File, line)) {
    std::stringstream ss(line);   // create ss object to split line based on space
    // save each value in a variable
    if (ss >> time_stamp >> x >> y >> theta >> beam_angle >> range >> x_endpoint >> y_endpoint) {
            
      if(range>0){
        x_.push_back(x); y_.push_back(y); theta_.push_back(theta);
        tot_count++;
              
        Eigen::Isometry2f iso;
        iso.linear() << cos(theta), -sin(theta), sin(theta), cos(theta);
            iso.translation() << x, y;
            Eigen::Vector2f p(range*cos(beam_angle), range*sin(beam_angle));
            p=iso*p;
                    
            if (p(0)-x_endpoint <= 0.1 || p(0)-x_endpoint>=-0.1  ){
            stamps.push_back(time_stamp); beam_angles.push_back( beam_angle ); ranges.push_back(range);
            neg_cnt++;
            os << p.transpose() << endl; 
                      } 
                     
       }
      
    }
  } //end of while
  /**
  print(x_); print(y_) ; print(theta_); 
  cerr << "______________________________ STAMPS______________________________" << endl; print(stamps); 
  cerr << "_________________________BEAM ANGLES ____________________________" << endl; print( beam_angles); 
  cerr << "_________________________RANGES ____________________________" << endl; print(ranges); **/
  cerr<< " I AM TOT AMOUNT " << tot_count << endl;
  cerr << "I am count with neg range" << neg_cnt << endl;
 
  MICP2D micp;
  // tv=0, rv=0;
  micp.X().setZero();
  micp.setMeasurement (ranges, stamps, beam_angles);
    
  while (1) {
	
   micp.oneRound();
    // char c;
    // cin >> c;
  }
 
 
}



