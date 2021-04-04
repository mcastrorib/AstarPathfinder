#ifndef GRID_H
#define GRID_H

// include C++ standard libraries
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>


// include OpenCV core functions
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

// include other PathFinder classes
#include "mNode.h"

#define OBSTACLES_RATE 0.4

using namespace std;

class mGrid
{
public:
	int gridSize;
	int gridDimX;
	int gridDimY;
	mNode *nodes;

	mGrid(int _dimX, int _dimY) : gridDimX(_dimX), gridDimY(_dimY), gridSize(_dimX*_dimY)
	{
		nodes = new mNode[gridSize];
		(*this).buildGridOfNodes();
	};

	mGrid(const mGrid &otherGrid)
	{
		this->gridSize = otherGrid.gridSize;
		this->gridDimX = otherGrid.gridDimX;
		this->gridDimY = otherGrid.gridDimY;
		this->nodes = otherGrid.nodes;
	}

	virtual ~mGrid()
	{
		if(nodes != NULL)
		{
			delete [] nodes;
			nodes = NULL;
		}
	}

	int getNodeIdx(int x, int y)
	{
		int index = this->gridDimX * y + x;
		index = index % gridSize;
		return index;
	}

	mNode getNode(int x, int y)
	{
		return this->nodes[getNodeIdx(x,y)];
	}

	vector<mNode *> getNeighbors(int _x, int _y)
	{
		cout << "getting node ("<< _x << ", " << _y << ") neighbors" << endl;
		vector<mNode*> neighbors(0);
		int index;
		if(_x-1 >= 0)
		{
			index = (*this).getNodeIdx(_x-1, _y);
			if(this->nodes[index].walkable) neighbors.push_back(&this->nodes[index]);
		} 
		
		if(_x+1 < this->gridDimX)
		{
			index = (*this).getNodeIdx(_x+1, _y);
			if(this->nodes[index].walkable) neighbors.push_back(&this->nodes[index]);		
		}

		if(_y-1 >= 0)
		{
			index = (*this).getNodeIdx(_x, _y-1);
			if(this->nodes[index].walkable) neighbors.push_back(&this->nodes[index]);
		} 
		 
		if(_y+1 < this->gridDimY)
		{
			index = (*this).getNodeIdx(_x, _y+1);
			if(this->nodes[index].walkable) neighbors.push_back(&this->nodes[index]);
		} 

		return neighbors;
	}

	void buildGridOfNodes()
	{
		bool walkable;
		int index;
		for(int j = 0; j < this->gridDimY; j++)
		{
			for(int i = 0; i < this->gridDimX; i++)
			{
				walkable = true;
				if((*this).getRandomDouble() < OBSTACLES_RATE) 
					walkable = false;
				index = (*this).getNodeIdx(i,j);
				this->nodes[index].set(i, j, walkable);
			}
		}
	}

	double getRandomDouble(double max=1.0, double min=0.0)
	{
	    std::random_device rd;
	    std::default_random_engine eng(rd());
	    std::uniform_real_distribution<double> distr(min, max);
    	return distr(eng);
	}	
};

#endif