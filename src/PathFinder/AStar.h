#ifndef ASTAR_H
#define ASTAR_H

// include C++ standard libraries
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <omp.h>

// include OpenCV core functions
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

// include other PathFinder classes
#include "mNode.h"
#include "mGrid.h"
#include "Canvas.h"

#define WALL_COLOR {10, 10, 10}
#define FREE_COLOR {127, 127, 127}
#define START_COLOR {0, 255, 255}
#define END_COLOR {214, 0, 110}
#define OPEN_COLOR {0, 200, 0}
#define CLOSED_COLOR {0, 0, 200}
#define PATH_COLOR {255, 255, 255}


using namespace std;

class AStar
{
public:
	mNode *startNode;
	mNode *endNode;
	mNode *path;
	Canvas *canvas;
	vector<mNode *> openSet;
	vector<mNode *> closedSet;
	bool visualize;
	int visualTimeRate;

	AStar(int _x, int _y) :  startNode(NULL), 
							 endNode(NULL), 
							 path(NULL),
							 visualize(false),
							 visualTimeRate(0)
	{		
		this->canvas = new Canvas(_x, _y);
		vector<mNode*> openSet();
		vector<mNode*> closedSet();

		(*this).drawGridNodes();
	}

	AStar(Canvas *_canvas) : startNode(NULL), 
							 endNode(NULL), 
							 path(NULL), 
							 canvas(_canvas),
							 visualize(false)
	{		
		vector<mNode*> openSet();
		vector<mNode*> closedSet();

		(*this).drawGridNodes();
	}

	AStar(const AStar &_other)
	{
		this->startNode = _other.startNode;
		this->endNode = _other.endNode;
		this->path = _other.path;
		this->canvas = _other.canvas;
		this->openSet = _other.openSet;
		this->closedSet = _other.closedSet;
		this->visualize = _other.visualize;
	}

	virtual ~AStar()
	{
		cout << "deleting Astar..." << endl;

		if(this->canvas != NULL)
		{
			delete this->canvas;
			this->canvas = NULL;
		}
		this->startNode = NULL;
		this->endNode = NULL;
		this->path = NULL;

		cout << "deleting Astar...Done" << endl;
	}

	void setVisualization(bool b=true, int time=0)
	{
		this->visualize = b;
		this->visualTimeRate = time;
	}

	void setStartNode(int x, int y)
	{
		int index = this->canvas->grid->getNodeIdx(x,y);
		this->startNode = &this->canvas->grid->nodes[index];
		this->startNode->walkable = true;
	}

	void setEndNode(int x, int y)
	{
		int index = this->canvas->grid->getNodeIdx(x,y);	
		this->endNode = &this->canvas->grid->nodes[index];	
		this->endNode->walkable = true;
	}

	void draw()
	{
		(*this).drawPoints();
	}

	void show(int time = 0)
	{
		if(this->canvas != NULL)
		{
			this->canvas->show(time);
		}
	}

	void drawPoints()
	{
		int posX, posY;
		if(this->startNode != NULL)
		{
			posX = this->startNode->x * this->canvas->nodeSizeX + this->startNode->x * this->canvas->gridLinewidth;
			posY = this->startNode->y * this->canvas->nodeSizeY + this->startNode->y * this->canvas->gridLinewidth;
			this->canvas->drawRectangle(posX, posY, START_COLOR, this->canvas->nodeSizeX, this->canvas->nodeSizeY);
		}

		if(this->endNode != NULL)
		{
			posX = this->endNode->x * this->canvas->nodeSizeX + this->endNode->x * this->canvas->gridLinewidth;
			posY = this->endNode->y * this->canvas->nodeSizeY + this->endNode->y * this->canvas->gridLinewidth;
			this->canvas->drawRectangle(posX, posY, END_COLOR, this->canvas->nodeSizeX, this->canvas->nodeSizeY);
		}

		if(this->openSet.size() > 0)
		{
			for (int node = 0; node < this->openSet.size(); node++)
			{
				int currentNodeX = this->openSet[node]->x;
				int currentNodeY = this->openSet[node]->y;
				posX = currentNodeX * this->canvas->nodeSizeX + currentNodeX * this->canvas->gridLinewidth;
				posY = currentNodeY * this->canvas->nodeSizeY + currentNodeY * this->canvas->gridLinewidth;
				this->canvas->drawRectangle(posX, posY, OPEN_COLOR, this->canvas->nodeSizeX, this->canvas->nodeSizeY);
			}
		}

		if(this->closedSet.size() > 0)
		{
			for (int node = 0; node < this->closedSet.size(); node++)
			{
				int currentNodeX = this->closedSet[node]->x;
				int currentNodeY = this->closedSet[node]->y;
				posX = currentNodeX * this->canvas->nodeSizeX + currentNodeX * this->canvas->gridLinewidth;
				posY = currentNodeY * this->canvas->nodeSizeY + currentNodeY * this->canvas->gridLinewidth;
				this->canvas->drawRectangle(posX, posY, CLOSED_COLOR, this->canvas->nodeSizeX, this->canvas->nodeSizeY);
			}
		}

		// draw current best path
		mNode *currentNode = this->path;
		while(currentNode != NULL)
		{
			int currentNodeX = currentNode->x;
			int currentNodeY = currentNode->y;
			posX = currentNodeX * this->canvas->nodeSizeX + currentNodeX * this->canvas->gridLinewidth;
			posY = currentNodeY * this->canvas->nodeSizeY + currentNodeY * this->canvas->gridLinewidth;
			this->canvas->drawRectangle(posX, posY, PATH_COLOR, this->canvas->nodeSizeX, this->canvas->nodeSizeY);

			// update current node
			currentNode = currentNode->previous;
		}  

	}

	void drawGridNodes()
	{
		int posX, posY;
		for(int j = 0; j < this->canvas->grid->gridDimY; j++)
		{
			for(int i = 0; i < this->canvas->grid->gridDimX; i++)
			{
				posX = i * this->canvas->nodeSizeX + i * this->canvas->gridLinewidth;
				posY = j * this->canvas->nodeSizeY + j * this->canvas->gridLinewidth;;
				mNode n = this->canvas->grid->getNode(i,j);	
				if(n.walkable)
				{
					this->canvas->drawRectangle(posX, posY, FREE_COLOR, this->canvas->nodeSizeX, this->canvas->nodeSizeY);
				} else
				{
					this->canvas->drawRectangle(posX, posY, WALL_COLOR, this->canvas->nodeSizeX, this->canvas->nodeSizeY);
				}
			}			
		}
	}
	

	void findPath()
	{
		double stime = omp_get_wtime();
		cout << "starting findPath() method..." << endl;
		
		this->startNode->setGValue(0.0);
		this->startNode->setHValue(this->endNode);
		this->openSet.push_back(this->startNode);
		mNode *currentNode = this->startNode;
		this->path = currentNode;
		int iter = 0;

		while(this->openSet.size() > 0)
		{
			iter++;
			if(iter % 100 == 0) 
				cout << "iter: " << iter << endl;			

			currentNode = (*this).getNodeWithLowestValue();
			this->closedSet.push_back(currentNode);
			this->path = currentNode;

			if(currentNode->compare(this->endNode))
			{
				this->path = this->endNode;
				break;
			}

			vector<mNode*> neighbors = this->canvas->grid->getConnectedNeighbors(currentNode->x, currentNode->y);
			for (int node = 0; node < neighbors.size(); node++)
			{
				bool closedSetContainsNode;
				if(std::find(this->closedSet.begin(), this->closedSet.end(), neighbors[node]) != this->closedSet.end())
				{ closedSetContainsNode = true; } else closedSetContainsNode = false;
				
				if(!closedSetContainsNode) 
				{
					double newPath = currentNode->getFValue() + 1.0;
					
					bool openSetContainsNode;
					if(std::find(this->openSet.begin(), this->openSet.end(), neighbors[node]) != this->openSet.end())
					{ openSetContainsNode = true; } else openSetContainsNode = false;	
					
					if(newPath < neighbors[node]->getFValue() or !openSetContainsNode)
					{	
						neighbors[node]->setPrevious(currentNode);
						neighbors[node]->setGValue(currentNode->gValue + 1.0);
						neighbors[node]->setHValue(this->endNode);
						
						if(!openSetContainsNode) 
							this->openSet.push_back(neighbors[node]);
					}
				}
			}

			// draw current stage
			if(this->visualize)
			{
				(*this).draw();
				(*this).show(this->visualTimeRate);
			}
		}

		stime = omp_get_wtime() - stime;
		cout << endl << "search time: " << stime << " secs" << endl; 
		if(this->path->compare(this->endNode)) 
			cout << "path to end node was found :)" << endl;
		else 
			cout << "no path found :(" << endl;
		
		// draw last stage
		(*this).draw();
		(*this).show();
	}

	mNode * getNodeWithLowestValue()
	{
		int lowestIdx = 0;
		mNode *currentNode = this->openSet[lowestIdx];
		mNode *nextNode;

		for(int node = 1; node < this->openSet.size(); node++)
		{
			nextNode = this->openSet[node];

			if(nextNode->getFValue() < currentNode->getFValue())
			{
				currentNode = nextNode;
				lowestIdx = node;
			} else if(nextNode->getFValue() == currentNode->getFValue())
			{
				if(nextNode->getHValue() < currentNode->getHValue())
				{
					currentNode = nextNode;
					lowestIdx = node;
				}
			}
		}

		(*this).removeFromOpenSet(lowestIdx);
		return currentNode;
	}

	void removeFromOpenSet(int index)
	{
		int lastIndex = this->openSet.size() - 1;
		swap(this->openSet[lastIndex], this->openSet[index]);
		this->openSet.pop_back();
	}
};

#endif