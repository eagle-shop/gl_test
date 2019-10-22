cmake_minimum_required(VERSION 3.1)
project(gl_test CXX)

if(APPLE)
    add_executable(gl_test cocoa.mm  main.cpp)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_executable(gl_test x11.cpp  main.cpp)
endif()

target_link_libraries(gl_test glfw)
