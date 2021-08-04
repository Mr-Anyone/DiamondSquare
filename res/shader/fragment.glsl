#version 330 core 
out vec4 fragColor;



struct Material{
    vec3 diffuse; 
    vec3 specular; 

    float shininess;
}; 

struct dirLight {
    vec3 direction; 
    
    vec3 ambient; 
    vec3 diffuse; 
    vec3 specular;    
};

struct pointLight{
    vec3 position;
    
    vec3 ambient; 
    vec3 diffuse; 
    vec3 specular;

    float constant;
    float linear; 
    float quadratic;
};

vec3 CalcPointLight(pointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcDirLight(dirLight light, vec3 normal, vec3 viewDir);

in vec3 normal;
in vec3 fragPos;

uniform vec3 viewPos;
uniform Material material;
uniform pointLight light;
uniform dirLight directionLight;


void main() {
    // White Color
    vec3 viewDir = (viewPos - fragPos);

    vec3 resultColor = CalcPointLight(light, normal, fragPos, viewDir);
    fragColor = vec4(resultColor, 1.0f);    
}

vec3 CalcPointLight(pointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient  * material.diffuse;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcDirLight(dirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * material.diffuse;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular);
}