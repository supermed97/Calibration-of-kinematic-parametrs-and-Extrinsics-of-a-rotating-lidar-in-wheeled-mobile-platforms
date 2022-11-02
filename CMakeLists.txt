cmake_minimum_required(VERSION 2.8.3)
project(lesson_6)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)


include_directories(. /usr/include/eigen3)
add_executable(sim simulator_test.cpp simulator.cpp)
add_executable(file_2_vec file_2_vec.cpp)
add_executable(deskewer eigen_micp_2d_utils.cpp eigen_micp_2d.cpp eigen_micp_2d_test.cpp )
add_executable(validate eigen_micp_2d_utils.cpp eigen_micp_2d.cpp validate_data.cpp )
add_executable(validate2 eigen_micp_2d_utils.cpp eigen_micp_2d.cpp validate_data_v0.cpp )

add_executable(create createp.cpp simulator.cpp)


