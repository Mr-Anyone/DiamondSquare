#ifndef MESH_H
#define MESH_H 

#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "shader.h"

class Mesh{
private: 
    unsigned int VAO, EBO, VBO;
    float* m_vertices;
    unsigned int* m_indices;
    
    std::size_t m_indicesSize; 
    std::size_t m_vertexSize;
    void loadData() ;
public:
    Mesh(float* vertices, unsigned int* indices, std::size_t vertices_size, std::size_t indices_size):
        m_indicesSize{indices_size}, m_vertexSize {vertices_size}
    {
        m_vertices = new float[vertices_size];
        m_indices = new unsigned int [indices_size]; 
        
        for(int i = 0; i<vertices_size; ++i)
            m_vertices[i] = vertices[i];
        
        for(int i = 0; i<indices_size; ++i)
            m_indices[i] = indices[i];
        
        this->loadData();
    }

    ~Mesh()
    {
        if(m_vertices != nullptr)
            delete [] m_vertices;
        
        if(m_indices != nullptr)
            delete [] m_indices;
    }

    // Assumed Shader is bound
    void draw() const;
    void draw(const Shader& shader) const;
}; 

#endif
