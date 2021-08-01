#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// This made may a terriable idea, as GLFWwindow may not be heap allocated memory therefore you should probably not return a window context
GLFWwindow* init(int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window {glfwCreateWindow(width, height, "Diamond Square Algorithm", nullptr, nullptr)};
    if(window == nullptr)
    {
        std::cerr << "Cannot Make Window Context" << std::endl; 
        std::exit(-1);
    }
    glfwMakeContextCurrent(window); 
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        std::exit(-1);
    }

    glViewport(0, 0, width, height);
    return window;
}



#endif