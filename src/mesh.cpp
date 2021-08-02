#include "mesh.h"
#include "terrain.h"
#include <vector>

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

Mesh makeTerrainMesh(){
    float** grid {new float* [TERRAIN_HEIGHT]};
    makeGrid(grid);
    makeDiamondSquareMesh(grid, 0, 2, Point{0, 0}, TERRAIN_HEIGHT - 1);

    // Debugging settings
    // printGrid(grid);
    
    // Making vertices 
    const std::size_t verticesSize = TERRAIN_WIDTH * TERRAIN_HEIGHT * 3;
    float* vertices {new float[verticesSize]}; 
    int count {0};
    for(int y=0; y<TERRAIN_HEIGHT; ++y)
    {
        for(int x =0; x<TERRAIN_WIDTH; ++x)
        {
            vertices[count] = x; 
            vertices[count + 1] = y; 
            vertices[count+ 2]  = grid[y][x];
            count += 3;
        }
    }

    //Making indices
    count = 0;
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

    // Mesh has to be made before deallocation happens
    Mesh terrainMesh  {vertices, indices, verticesSize, indicesSize};
    
    // Remeber to deallocate grid 
    delete [] vertices; 
    // grid is a two dimensional array
    for(int i=0; i<TERRAIN_HEIGHT; ++i)
        delete [] grid[i];
    delete [] grid; 
    delete [] indices;

    return terrainMesh;
}