cmake_minimum_required(VERSION 3.1)

project(gl_test CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(./dependencies/glfw/include/GLFW)

add_subdirectory(./dependencies)
add_subdirectory(./src)
