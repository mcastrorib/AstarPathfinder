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
#define GRID_SIZE 10

using namespace std;
using namespace cv;

// Main Program
int main(int argc, char *argv[])
{    
    Canvas *canvas = new Canvas(new mGrid(GRID_SIZE, GRID_SIZE));
    canvas->show();

    // Initalize pathfinder then set start and end points
    AStar *pathfinder = new AStar(canvas);
    pathfinder->show();
    pathfinder->setStartNode(0, 0);
    pathfinder->setEndNode(GRID_SIZE - 1, GRID_SIZE - 1);
    pathfinder->draw();
    pathfinder->show();

    pathfinder->findPath();
    pathfinder->draw();
    pathfinder->show();

    // close app
    delete canvas;
    canvas = NULL;
    return 0;
}

void debug()
{    
    cout << "hey, hello there!" << endl;

    Mat image(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC3, Scalar(127, 127, 127));
    int channels = image.channels();
    unsigned int microseconds = 100000;
    namedWindow("Display window", WINDOW_AUTOSIZE); //Create a window for display
    imshow("Display window", image);
    waitKey(0); // Wait for a keystroke in the window

    for (uint y = 0; y < IMAGE_HEIGHT; y++)
    {
        uchar *current_pixel;
        current_pixel = image.ptr<uchar>(y);
        current_pixel[y*channels + 0] = 0;
        current_pixel[y*channels + 1] = 0;
        current_pixel[y*channels + 2] = 255;

        imshow("Display window", image);
        waitKey(15); // Wait 100 ms to close image
    }

    // Show final image
    imshow("Display window", image);
    waitKey(0); // Wait for a keystroke in the window
}