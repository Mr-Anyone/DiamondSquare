#ifndef LIHGT_H
#define LIGHT_H 

#include <glm/glm.hpp>
#include "shader.h"

struct PointLight{    
    glm::vec3 ambient; 
    glm::vec3 diffuse; 
    glm::vec3 specular; 
    
    float constant; 
    float linear; 
    float quadratic;
};

struct Material{
    glm::vec3 ambient;
    glm::vec3 diffuse; 
    glm::vec3 specular; 
    float shininess;
};

namespace LightSettings{
    namespace Materials{
        const Material gold {glm::vec3(0.24725, 0.1995, 0.0745), glm::vec3(0.75164, 0.60648, 0.22648), glm::vec3(0.628281, 0.555802, 0.366065), 0.4};
    };
    namespace PointLights{
        const PointLight whiteLight {glm::vec3(1.01f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.07f, 0.017f};
    };
    
}; 

void setPointLight(const Shader& shader, const glm::vec3& cameraPosition, const glm::vec3& lightPosition, const PointLight& light, const Material& material);
// void setDirLight(const Shader& shader, const Material& material);

#endif 