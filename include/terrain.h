#ifndef TERRAIN_H 
#define TERRAIN_H

#define TERRAIN_HEIGHT 9
#define TERRAIN_WIDTH 9

struct Point
{
    int x; 
    int y;
};

void printGrid(float**grid);

void makeGrid(float** grid);

float gridAverage(float**grid, Point topRight, Point topLeft, Point bottomLeft, Point bottomRight);

void diamondStep(float**grid, Point topLeft, int boxLength, float average, float startRange, float endRange);

void squareStep(float ** grid, Point topLeft,  Point bottomRight, float average, int startRange, int endRange, int length);

void makeDiamondSquareMesh(float**grid, float startRange, float endRange, Point topLeft, int boxLength);

#endif