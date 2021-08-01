#include <iostream>
#include <random>
#include "terrain.h"

static float getRandomValue(float startRange, float endRange)
{
    static std::random_device rd; 
    static std::mt19937 gen (rd()); 
    
    std::uniform_real_distribution<float> dis(startRange, endRange);
    return dis(gen); 
}

void printGrid(float**grid)
{
    std::cout << "=====================================================" << std::endl;
    for(int y=0; y<TERRAIN_HEIGHT; ++y)
    {
        for(int x = 0; x<TERRAIN_WIDTH; ++x)
        {
            std::cout << grid[y][x] << "  ";
        }
        std::cout << "\n" << std::endl;
    }
    std::cout << "=====================================================" << std::endl;
}
void makeGrid(float** grid)
{
    for(int y = 0; y<TERRAIN_HEIGHT; ++y)
    {
        grid[y] = new float [TERRAIN_WIDTH]; 
        
        // Set the default value of the grid as zero
        for(int x = 0; x<TERRAIN_WIDTH; ++x){
            grid[y][x] = 0.0f;
        }
    }
}


float gridAverage(float**grid, Point topRight, Point topLeft, Point bottomLeft, Point bottomRight)
{
    return (grid[topRight.y][topRight.x] + grid[topLeft.y][topLeft.x] + grid[bottomLeft.y][bottomLeft.x] + grid[bottomRight.y][bottomRight.x]) / 4;
}


void diamondStep(float**grid, Point topLeft, int boxLength, float average, float startRange, float endRange)
{
    Point boxCenter {topLeft.x + boxLength / 2,  topLeft.y + boxLength / 2 };
    grid[boxCenter.y][boxCenter.x] = average + getRandomValue(startRange, endRange);
}

void squareStep(float ** grid, Point topLeft,  Point bottomRight, float average, int startRange, int endRange, int length)
{
    length /= 2 ;
    grid[topLeft.y][topLeft.x  + length] = average + getRandomValue(startRange, endRange);
    grid[topLeft.y + length][topLeft.x] = average + getRandomValue(startRange, endRange);
    grid[bottomRight.y - length][bottomRight.x] = average + getRandomValue(startRange, endRange);
    grid[bottomRight.y][bottomRight.x - length] = average + getRandomValue(startRange, endRange);
}

void makeDiamondSquareMesh(float**grid, float startRange, float endRange, Point topLeft, int boxLength)
{
    // Finding the coroners    
    Point topRight {topLeft.x + boxLength, topLeft.y};
    Point bottomLeft {topLeft.x, topLeft.y + boxLength};
    Point bottomRight {topLeft.x + boxLength, topLeft.y + boxLength};
    
    // Doing Diamong Step
    float average {gridAverage(grid, topRight, topLeft, bottomLeft, bottomRight)}; 
    diamondStep(grid, topLeft, boxLength, average, startRange, endRange); 
    
    // Doing Square Step
    squareStep(grid, topLeft,  bottomRight, average, startRange, endRange, boxLength); 

    // Print Grid for debugging
    // printGrid(grid);

    // Call this again
    if(boxLength == 2){
        return;
    }
    boxLength /= 2;
    for(int i = 0; i<2; ++i)
    {
        for(int x = 0; x<2; ++x)
        {
            makeDiamondSquareMesh(grid, startRange/2 , endRange/2, Point {topLeft.x + (i*boxLength), topLeft.y + (x*boxLength)}, boxLength);
        }
    }

}
