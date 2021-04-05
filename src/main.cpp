// include C++ standard libraries
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>

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

// include CMake Configuration file
#include "pathfinder_config.h"


#define IMAGE_HEIGHT 1000
#define IMAGE_WIDTH 1000
#define GRID_SIZE 100

using namespace std;
using namespace cv;

// Main Program
int main(int argc, char *argv[])
{        
    // Initalize pathfinder then set start and end points
    AStar *pathfinder = new AStar(GRID_SIZE, GRID_SIZE);
    pathfinder->setVisualization(true, 1);
    pathfinder->setStartNode(0, 0);
    pathfinder->setEndNode(GRID_SIZE - 1, GRID_SIZE - 1);
    pathfinder->draw();
    pathfinder->show();
    pathfinder->findPath();

    // close app
    delete pathfinder;
    pathfinder = NULL;
    return 0;
}