#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"

#include "camera.h"
#include "shader.h"
#include "terrain.h"
#include "mesh.h"

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

void draw(const Shader& shader)
{
    shader.use(); 
}


int main() 
{
    GLFWwindow* window = init(width_g, height_g); 
    Shader shader ("./../res/shader/vertex.glsl", "./../res/shader/fragment.glsl");
    float vertices [] = {
        0.5f, -0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f, 
        0.0f, 0.5f, 0.0f
    };
    unsigned int indices [] = {
        0, 1, 2
    };
    Mesh mesh (vertices, indices, 9, 3); 

    while(!glfwWindowShouldClose(window))
    {
        clearScreen();

        shader.use();
        mesh.draw(shader);

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }
    return 0;
}
