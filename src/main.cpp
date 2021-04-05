// include C++ standard libraries
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <map>

// include OpenCV core functions
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

// include PathFinder headers
#include "mNode.h"
#include "mGrid.h"
#include "Canvas.h"
#include "AStar.h"
#include "mHeap.h"


// include CMake Configuration file
#include "pathfinder_config.h"

#define GRID_SIZE 100
#define REAL_TIME_VISUAL true
#define VISUAL_RATE 1
#define DRAW_OPEN_SET true
#define DRAW_CLOSED_SET true


using namespace std;

int getRandomInt(int max, int min=0)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distr(min, max);
    return distr(rng);
}	

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
    pathfinder->draw(); 
    pathfinder->show(); 
    pathfinder->findPath();  

    // close app
    cout << endl << "closing app" << endl;
    delete pathfinder;
    pathfinder = NULL;
    return 0;
}

