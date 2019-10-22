#include <iostream>
#include "mywindow.h"
#include "glfw3.h"

int main(){
    std::cout << "main" << std::endl;
    sub();

    if(!glfwInit()){
        return (-1);
    }

    return 0;
}
