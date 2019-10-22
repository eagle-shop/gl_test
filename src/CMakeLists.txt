cmake_minimum_required(VERSION 3.1)
project(gl_test CXX)

if(APPLE)
    add_executable(main cocoa.mm  main.cpp)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_executable(main x11.cpp  main.cpp)
endif()
