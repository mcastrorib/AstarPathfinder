// include C++ standard libraries
#include <unistd.h>
#include <iostream>
#include <random>

// include CMake Configuration file
#include "pathfinder_config.h"

#include "AStar.h"

int getRandomInt(int max, int min=0);

// Main Program
int main(int argc, char *argv[])
{        
    // Initalize pathfinder then set start and end points
    AStar *pathfinder = new AStar(GRID_SIZE, GRID_SIZE);
    pathfinder->setStartNode(0,0); 
    pathfinder->setEndNode(GRID_SIZE-1, GRID_SIZE-1);
    pathfinder->setVisualization(REAL_TIME_VISUAL, VISUAL_RATE); 
    pathfinder->setDrawOpenSet(DRAW_OPEN_SET);
    pathfinder->setDrawClosedSet(DRAW_CLOSED_SET);
    if(ALLOW_DIAGONAL_MOVEMENT) pathfinder->setGridConnectivity(8);
    pathfinder->draw(); 
    pathfinder->show(); 
    pathfinder->findPath();  

    // close app
    cout << endl << "closing app" << endl;
    delete pathfinder;
    pathfinder = NULL;
    return 0;
}

int getRandomInt(int max, int min)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distr(min, max);
    return distr(rng);
}	