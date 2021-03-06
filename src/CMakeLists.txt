cmake_minimum_required(VERSION 3.1)
project(gl_test CXX)

if(APPLE)
    add_executable(gl_test cocoa.mm  main.cpp)
    target_link_libraries(gl_test /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/IOKit.framework)
    target_link_libraries(gl_test /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Cocoa.framework)
    target_link_libraries(gl_test /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/CoreVideo.framework)
    target_link_libraries(gl_test /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/OpenGL.framework)
    target_compile_definitions(gl_test PUBLIC NDEBUG GL_SILENCE_DEPRECATION)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_executable(gl_test x11.cpp  main.cpp)
    target_link_libraries(gl_test GL)
    target_compile_definitions(gl_test PUBLIC NDEBUG GL_GLEXT_PROTOTYPES)
endif()

if(WIN32)
    add_executable(gl_test win32.cpp  main.cpp)
    target_link_libraries(gl_test glew32.lib)
    target_link_libraries(gl_test libopengl32.a)
    target_compile_definitions(gl_test PUBLIC NDEBUG GL_GLEXT_PROTOTYPES)
    target_compile_definitions(gl_test PUBLIC NDEBUG GLFW_INCLUDE_GLEXT)
    target_compile_definitions(gl_test PUBLIC NDEBUG _WINDOWS)
endif()

target_link_libraries(gl_test glfw)
target_link_libraries(gl_test freetype)
