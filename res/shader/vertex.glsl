#version 330 core 
layout (location=0) in vec3 aPosition;
layout (location=1) in vec3 aNormal;

uniform mat4 projection; 
uniform mat4 view; 
uniform mat4 model;

out vec3 normal;
out vec3 fragPos;

void main(){
    gl_Position = projection * view * model * vec4(aPosition, 1.0f); 
    normal = (model * vec4(normalize(aNormal), 1.0f)).xyz;
    fragPos = (model * vec4(aPosition, 1.0f)).xyz;
}