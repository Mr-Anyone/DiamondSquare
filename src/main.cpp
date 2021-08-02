#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"

#include "camera.h"
#include "shader.h"
#include "terrain.h"
#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr int width_g {1920}; 
constexpr int height_g {1080}; 

// Global variable for view 
Camera camera_g {glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)};
const glm::mat4 projection_g {glm::perspective(glm::radians(45.0f), static_cast<float> (width_g) / height_g, 0.1f, 100.0f)};

void clearScreen()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void processInput(GLFWwindow* window)
{
    constexpr float cameraSpeed {1.0f};

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); 
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_g.moveFront(cameraSpeed);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_g.moveFront(-cameraSpeed);
    
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_g.moveSide(cameraSpeed);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_g.moveSide(-cameraSpeed);
    

}

void draw(const Shader& shader, const Mesh& mesh)
{
    glm::mat4 model (1.0f);

    shader.use(); 
    // Think of a better way to achieve this
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection_g));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(camera_g.getView()));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4 (model)));
    mesh.draw();
}

void drawTerrain(const Shader& shader, const Mesh& mesh)
{
    glm::mat4 model (1.0f);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    
    shader.use(); 
    // Think of a better way to achieve this
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection_g));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(camera_g.getView()));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4 (model)));
    mesh.draw();
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    static double lastX, lastY; 
    static bool first {true};
    if(first){
        lastX = xPos;
        lastY = yPos;
        first = false;
        return;
    }

    camera_g.rotate( xPos - lastX, lastY - yPos);
    lastX = xPos;
    lastY = yPos;
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
    Mesh terrain = makeTerrainMesh();
    
    // Camera and mouse callback 
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glfwSetCursorPosCallback(window, mouseCallback);  
    glEnable(GL_DEPTH_TEST);  
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        clearScreen();

        // draw(shader, mesh);
        drawTerrain(shader, terrain);

        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }
    return 0;
}
