#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <tuple>
#include <thread>
#include <chrono>
#ifdef _WINDOWS
#include <GL/glew.h>
#endif // _WINDOWS
#include "glfw3.h"
#include "mywindow.h"

constexpr int g_width  = 640;
constexpr int g_height = 480;

using VertexPosition = std::array<std::array<float, 2>, 4>;
using VertexColor = std::array<std::array<float, 4>, 4>;
using RectAttr = std::tuple<VertexPosition, VertexColor>;

GLuint crateShader(){
    GLuint vShaderId = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShader = R"#(
    attribute vec3 vPosition;
    attribute vec4 vColor;
    varying vec4 color;
    void main(void){
        gl_Position = vec4(vPosition, 1.0);
        color = vColor;
    }
    )#";
    const char* vs = vertexShader.c_str();
    glShaderSource(vShaderId, 1, &vs, NULL);
    glCompileShader(vShaderId);

    GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShader = R"#(
    varying vec4 color;
    void main(void){
        gl_FragColor = color;
    }
    )#";
    const char* fs = fragmentShader.c_str();
    glShaderSource(fShaderId, 1, &fs, NULL);
    glCompileShader(fShaderId);

    GLuint programId = glCreateProgram();
    glAttachShader(programId,vShaderId);
    glAttachShader(programId,fShaderId);

    glLinkProgram(programId);
    glUseProgram(programId);

    return programId;
}

int main(){
    std::cout << "main" << std::endl;
    sub();

    if(!glfwInit()){
        return (-1);
    }

    GLFWwindow* window = glfwCreateWindow(g_width, g_height, "gl_test", NULL, NULL);
    if(!window){
        glfwTerminate();
        return (-1);
    }

    glfwMakeContextCurrent(window);
#ifdef _WINDOWS
    glewExperimental = GL_TRUE;
    GLenum res = glewInit();
    if(res != GLEW_OK){
        std::cout << "glewInit error" << std::endl;
        return (-1);
    }
#endif // _WINDOWS
    glfwSwapInterval(1);

    const GLuint programId = crateShader();

    std::vector<RectAttr> rect = {
        {{{
            {-0.9f, 0.9f},
            {-0.1f, 0.9f},
            {-0.1f, 0.1f},
            {-0.9f, 0.1f},
        }},
        {{
            {1.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 1.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 0.0f, 1.0f},
        }}},
        {{{
            {0.1f, 0.9f},
            {0.9f, 0.9f},
            {0.9f, 0.1f},
            {0.1f, 0.1f},
        }},
        {{
            {0.0f, 1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 1.0f, 1.0f},
            {0.0f, 0.0f, 1.0f, 1.0f},
        }}},
    };

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0);

        // draw rect
        for(const auto& e : rect){
            const int attPosition = glGetAttribLocation(programId, "vPosition");
            glEnableVertexAttribArray(attPosition);
            glVertexAttribPointer(attPosition, 2, GL_FLOAT, false, 0, std::get<VertexPosition>(e).data());

            const int attColor = glGetAttribLocation(programId, "vColor");
            glEnableVertexAttribArray(attColor);
            glVertexAttribPointer(attColor, 4, GL_FLOAT, false, 0, std::get<VertexColor>(e).data());

            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    glfwTerminate();

    return 0;
}
