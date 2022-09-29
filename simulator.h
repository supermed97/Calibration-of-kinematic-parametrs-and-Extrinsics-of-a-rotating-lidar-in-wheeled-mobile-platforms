#pragma once
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/StdVector>
#include <vector>
#include <string>
using Vector3f=Eigen::Vector3f;
using Vector2f=Eigen::Vector2f;
using Vector2fVector=std::vector<Eigen::Vector2f, Eigen::aligned_allocator<Eigen::Vector2f> >;
using Matrix2fVector=std::vector<Eigen::Matrix2f, Eigen::aligned_allocator<Eigen::Matrix2f> >;
struct position
{     
	float theta;
	float delta_x;
	float delta_y; };
	
struct lines_elements{
	Vector2f line_p0;
	Vector2f line_dir;
	
	};	
void write_to_file(std::string filename, std::string text);
	
float polinomial(float theta, char dir);
	
float theta(int tick_r, int tick_l,float k_l, float k_r, float b);

float  x(int tick_r, int tick_l,float k_l, float k_r, float b,float theta);

float  y(int tick_r, int tick_l,float k_l, float k_r, float b,float theta);

float delta_s(float r, float omega_r, float omega_l, float T);

float delta_theta(float r, float omega_r, float omega_l, float T, float b);

std::vector<float> quad_solver(float a, float b, float c);

Vector2f create_ray(position *Pose_robot, float ray_angle);

Vector2f cast_ray(position *Pose_robot, Vector2f ray_dir, Vector2fVector& ray_points, std::string filename, Vector2fVector intersections);

void map_to_file(std::string filename, Vector2fVector& vec_of_points);

void drawLine(Vector2fVector& dest,
              const Vector2f& p0,
              const Vector2f& p1,
float density, lines_elements *line_elem);

Vector2f calc_intersection(Vector2f P0, Vector2f line_dir, position *Pose_robot,  Vector2f ray_dir );

float norm2d(Vector2f Start, Vector2f End);
