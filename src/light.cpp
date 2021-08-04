#include "light.h"

void setPointLight(const Shader& shader, const glm::vec3& cameraPosition, const glm::vec3& lightPosition, const PointLight& light, const Material& material)
{
    // Define  direction light, pointlight, camera pos, light pos 
    shader.setVec3("viewpos", cameraPosition.x, cameraPosition.y,  cameraPosition.z);
    
    // Material
    shader.setVec3("material.ambient", material.ambient.x, material.ambient.y, material.ambient.z);
    shader.setVec3("material.diffuse", material.diffuse.x, material.diffuse.y, material.diffuse.z);
    shader.setVec3("material.specular", material.specular.x, material.specular.y, material.specular.z);
    shader.setFloat("material.shininess", material.shininess);

    // Point Light
    shader.setVec3("light.position", lightPosition.x, lightPosition.y, lightPosition.z); 
    shader.setVec3("light.ambient", light.ambient.x, light.ambient.y, light.ambient.z); 
    shader.setVec3("light.diffuse", light.diffuse.x, light.diffuse.y, light.diffuse.z); 
    shader.setVec3("light.specular", light.specular.x, light.specular.y, light.specular.z); 
    shader.setFloat("light.constant", light.constant);
    shader.setFloat("light.linear", light.linear);
    shader.setFloat("light.quadratic", light.quadratic);
}

void setDirLight(const Shader& shader, const Material& material)
{

}