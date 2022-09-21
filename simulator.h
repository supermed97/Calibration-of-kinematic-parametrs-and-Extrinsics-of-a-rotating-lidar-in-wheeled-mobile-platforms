#pragma once
struct position
{     
	float theta;
	float delta_x;
	float delta_y; };
	
float polinomial(float theta, char dir);
	
float theta(int tick_r, int tick_l,float k_l, float k_r, float b);

float  x(int tick_r, int tick_l,float k_l, float k_r, float b,float theta);

float  y(int tick_r, int tick_l,float k_l, float k_r, float b,float theta);

float delta_s(float r, float omega_r, float omega_l, float T);

float delta_theta(float r, float omega_r, float omega_l, float T, float b);

std::vector<float> quad_solver(float a, float b, float c);
