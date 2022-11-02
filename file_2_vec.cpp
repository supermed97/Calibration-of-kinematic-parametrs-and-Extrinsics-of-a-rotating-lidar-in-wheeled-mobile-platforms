#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
using std::istringstream;
using std::ifstream;
using std::string;
using std::cout;
using std::vector;

void print(std::vector<float> vector){
	for (auto& elem:vector){
		cout << elem << endl;
	}
	//cout <<endl;
}

int main()
{
	float time_stamp, x,y,theta;
    float beam_angle, range;
	string instruction,line;
    vector<float> trajectory;
    ifstream input_File;
    input_File.open("micp_file.dat");
    
     if(input_File.fail()) // checks to see if file opended 
    { 
      cout << "error COULDNT OPEN FILE " << endl; 
      return 1; // no point continuing if the file didn't open...
    } 
    
    std::vector<float> stamps;   // work vector 1
    std::vector<float> beam_angles; // work vector 2    
    std::vector<float> ranges;
while (std::getline(input_File, line))
{
    std::stringstream ss(line);  
   
            if (ss >> time_stamp >> x >> y >> theta >> beam_angle >> range)
    {
		 cout<<time_stamp << ' ' << beam_angle <<' ' << range << endl;
          stamps.push_back(time_stamp); beam_angles.push_back(beam_angle); ranges.push_back(range);
    }
} //end of while

/** PRINT VECTORS ****/
 cout  << "______________________________ STAMPS______________________________" << endl; print(stamps); 
 cout << "_________________________BEAM ANGLES ____________________________" << endl; print( beam_angles); 
  cout << "_________________________RANGES ____________________________" << endl; print(ranges);

return 0;
}
