#include <iostream> 
#include <random>
#include "terrain.h"

int main()
{
    float** grid {new float* [TERRAIN_HEIGHT]}; 
    makeGrid(grid);
    makeDiamondSquareMesh(grid,  0, 2, Point {0, 0}, TERRAIN_WIDTH - 1);
    printGrid(grid);

    return 0; 
}