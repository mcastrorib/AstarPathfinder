#ifndef PATHFINDER_H
#define PATHFINDER_H

// include C++ standard libraries
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits>
#include <random>
#include <omp.h>

// include opencv libraries
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

// define macros
// grid
#define GRID_SIZE 20
#define OBSTACLES_RATE 0.2
#define GRID_WALKABLE_COLOR 127

// canvas
#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 800
#define GRID_LINEWIDTH 1

// colors
#define BG_COLOR {127, 127, 127}
#define GRID_COLOR {0, 0, 0}
#define WALL_COLOR {10, 10, 10}
#define FREE_COLOR {150, 150, 150}
#define OPEN_COLOR {112, 112, 0}
#define CLOSED_COLOR {80, 80, 0}
#define START_COLOR {0, 0, 110}
#define END_COLOR {0, 0, 220}
#define PATH_COLOR {0, 0, 230}

// pathfinding
#define REAL_TIME_VISUAL true
#define VISUAL_RATE 1
#define DRAW_OPEN_SET true
#define DRAW_CLOSED_SET true
#define ALLOW_DIAGONAL_MOVEMENT true

// include PathFinder lib classes
#include "mNode.h"
#include "mGrid.h"
#include "mHeap.h"
#include "Canvas.h"
#include "AStar.h"
#include "PathFinderApp.h"

#endif