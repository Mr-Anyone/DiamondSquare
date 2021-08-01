#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"

constexpr int width_g {800}; 
constexpr int height_g {600}; 

void clearScreen()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); 
}

int main() 
{
    GLFWwindow* window = init(width_g, height_g); 
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        clearScreen();
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }
    return 0;
}
