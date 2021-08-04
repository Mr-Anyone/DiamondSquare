#include "mesh.h"
#include "terrain.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Mesh::loadData() 
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertexSize, m_vertices, GL_STATIC_DRAW);

    // Position    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0); 

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m_indicesSize, m_indices, GL_STATIC_DRAW); 

    glBindVertexArray(0);
}

void TerrainMesh::loadData() {
    std::cout << "Terrain Mesh Loading Data" << std::endl;
    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO); 
    glGenBuffers(1, &EBO); 

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertexSize, m_vertices, GL_STATIC_DRAW); 

    // Vertex Data in format (position x, position y, position z, normal x, normal y, normal z)
    // Position Data 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Normal Data 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);


    // EBO 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m_indicesSize, m_indices, GL_STATIC_DRAW); 

    // Unbind vertex array
    glBindVertexArray(0);
}

void Mesh::draw() const{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glDrawElements(GL_TRIANGLES, m_indicesSize, GL_UNSIGNED_INT, 0);
}

void Mesh::draw(const Shader& shader) const
{
    shader.use(); 

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glDrawElements(GL_TRIANGLES, m_indicesSize, GL_UNSIGNED_INT, 0);
}
static unsigned int grabIndicesLocation(int y, int x){
    return y * TERRAIN_HEIGHT + x;
}

TerrainMesh makeTerrainMesh(){
    float** grid {new float* [TERRAIN_HEIGHT]};
    makeGrid(grid);
    makeDiamondSquareMesh(grid, 0, 2, Point{0, 0}, TERRAIN_HEIGHT - 1);

    // Debugging settings
    // printGrid(grid);

    //Making indices
    int count {0};
    const std::size_t indicesSize = (TERRAIN_HEIGHT - 1) * (TERRAIN_WIDTH - 1) * 6;
    unsigned int* indices {new unsigned int[indicesSize]};
    for(int y =0; y<TERRAIN_HEIGHT - 1; ++y) // Don't loop throught the last layer as this is already created
    {
        for(int x =0; x<TERRAIN_WIDTH - 1; ++x)
        {
            // Triangle One
            indices[count] = grabIndicesLocation(y, x);
            indices[count + 1] = grabIndicesLocation(y + 1, x);
            indices[count + 2] = grabIndicesLocation(y + 1, x + 1);

            // Triangle Two 
            indices[count + 3] = grabIndicesLocation(y, x);
            indices[count + 4]= grabIndicesLocation(y , x + 1);
            indices[count + 5] = grabIndicesLocation(y + 1, x + 1);

            count += 6;
        }
    }
    
    // Making vertices 
    const std::size_t verticesSize = TERRAIN_WIDTH * TERRAIN_HEIGHT * 6;
    float* vertices {new float[verticesSize]}; 
    count = 0;
    for(int y=0; y<TERRAIN_HEIGHT; ++y)
    {
        for(int x =0; x<TERRAIN_WIDTH; ++x)
        {
            vertices[count] = x; 
            vertices[count + 1] = y; 
            vertices[count+ 2]  = grid[y][x];
            count += 6;
        }
    }

    // Calculating Normals
    count = 0;
    for(int i = 0;i<indicesSize; i += 3)
    {
        // Point in a triangle
        unsigned int pA, pB, pC; // Point one, point two, ponit three
        pA = indices[i]; 
        pB = indices[i + 1]; 
        pC = indices [i + 2];

        // Vector
        glm::vec3  vecA {vertices[pA * 6], vertices[pA * 6 + 1], vertices[pA * 6 + 2]};
        glm::vec3  vecB {vertices[pB * 6], vertices[pB * 6 + 1], vertices[pB * 6 + 2]};
        glm::vec3  vecC {vertices[pC * 6], vertices[pC * 6 + 1], vertices[pC * 6 + 2]};

        // Normal Formula https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal
        glm::vec3 U = vecB - vecA; 
        glm::vec3 V = vecC - vecA; 

        // May not be normalized, will be normalized in vertex shader
        float nX = (U.y * V.z) - (U.z * V.y); 
        float nY = (U.z * V.x) - (U.x * V.z); 
        float nZ = (U.x * V.y) - (U.y * V.x); 

        // Set vertex normal 
        vertices[pA * 6 + 3] = nX;
        vertices[pA * 6 + 4] = nY;
        vertices[pA * 6 + 5] = nZ;
        
        vertices[pB * 6 + 3] = nX;
        vertices[pB * 6 + 4] = nY;
        vertices[pB * 6 + 5] = nZ;
        
        vertices[pC * 6 + 3] = nX;
        vertices[pC * 6 + 4] = nY;
        vertices[pC * 6 + 5] = nZ;
    }

    // Mesh has to be made before deallocation happens
    TerrainMesh terrainMesh  {vertices, indices, verticesSize, indicesSize};
    
    // Remeber to deallocate grid 
    delete [] vertices; 
    // grid is a two dimensional array
    for(int i=0; i<TERRAIN_HEIGHT; ++i)
        delete [] grid[i];
    delete [] grid; 
    delete [] indices;
    return terrainMesh;
}