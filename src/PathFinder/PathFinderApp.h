#ifndef APP_H
#define APP_H

// include Configuration file
#include "PathFinder.h"

using namespace std;

class PathFinderApp
{
private:
    AStar *aStar;
public:
    PathFinderApp(int _dimX, int _dimY)
    {
        this->aStar = new AStar(GRID_SIZE, GRID_SIZE);
        this->aStar->setVisualization(REAL_TIME_VISUAL, VISUAL_RATE); 
        this->aStar->setDrawOpenSet(DRAW_OPEN_SET);
        this->aStar->setDrawClosedSet(DRAW_CLOSED_SET);
        if(ALLOW_DIAGONAL_MOVEMENT) this->aStar->setGridConnectivity(8);
        this->aStar->setStartNode(0,0); 
        this->aStar->setEndNode(GRID_SIZE-1, GRID_SIZE-1);
        this->aStar->draw(); 
        this->aStar->show(); 
    }

    PathFinderApp(cv::Mat *image)
    {
        mGrid *imageGrid = new mGrid(image);
        this->aStar = new AStar(imageGrid);
        this->aStar->setStartNode(0,0); 
        this->aStar->setEndNode(GRID_SIZE-1, GRID_SIZE-1);
        this->aStar->setVisualization(REAL_TIME_VISUAL, VISUAL_RATE); 
        this->aStar->setDrawOpenSet(DRAW_OPEN_SET);
        this->aStar->setDrawClosedSet(DRAW_CLOSED_SET);
        if(ALLOW_DIAGONAL_MOVEMENT) this->aStar->setGridConnectivity(8);
        this->aStar->draw(); 
        this->aStar->show();  
    }

    PathFinderApp(string imagePath)
    {
        cv::Mat *image;
        image = new cv::Mat(cv::imread(imagePath));
        mGrid *imageGrid = new mGrid(image);
        this->aStar = new AStar(imageGrid);
        this->aStar->setVisualization(REAL_TIME_VISUAL, VISUAL_RATE); 
        this->aStar->setDrawOpenSet(DRAW_OPEN_SET);
        this->aStar->setDrawClosedSet(DRAW_CLOSED_SET);
        if(ALLOW_DIAGONAL_MOVEMENT) this->aStar->setGridConnectivity(8);
        this->aStar->getStartNode(); 
        this->aStar->draw();
        this->aStar->getEndNode();
        this->aStar->draw(); 
        this->aStar->show(); 
    }

    virtual ~PathFinderApp()
    {
        if(this->aStar != NULL)
        {
            delete this->aStar;
            this->aStar = NULL;
        }
    }

    void run()
    {
        this->aStar->findPath(); 
    }
};

#endif