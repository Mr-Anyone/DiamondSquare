#ifndef MESH_H
#define MESH_H 

#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "shader.h"
#include "terrain.h"

// IMPORTANT: Think of a way to do copying and moving data around

class Mesh{
protected: 
    unsigned int VAO, EBO, VBO;
    float* m_vertices;
    unsigned int* m_indices;

    std::size_t m_indicesSize; 
    std::size_t m_vertexSize;
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
    }

    ~Mesh()
    {
        if(m_vertices != nullptr)
            delete [] m_vertices;
        
        if(m_indices != nullptr)
            delete [] m_indices;
    }
    // Think of a move contructor

    // Assumed Shader is bound
    virtual void draw() const;
    virtual void draw(const Shader& shader) const;

    // To load data, you have explicitly call this function
    virtual void loadData();
}; 

// The only difference is that terrain mesh will have normal vectors in its vertices
class TerrainMesh: public Mesh
{
protected:
    virtual void loadData() ;
public: 
    TerrainMesh(float* vertices, unsigned int *indices, std::size_t verticesSize, std::size_t indicesSize):
        Mesh {vertices, indices, verticesSize, indicesSize}
    {
        TerrainMesh::loadData();
    }

    ~TerrainMesh()
    {
        std::cout << "Deallocate memory" << std::endl;
    }
};

TerrainMesh makeTerrainMesh();
#endif
