#ifndef ASTAR_H
#define ASTAR_H

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

// include other PathFinder classes
#include "mNode.h"
#include "mGrid.h"
#include "Canvas.h"

#define WALL_COLOR {50, 50, 50}
#define FREE_COLOR {200, 200, 200}
#define START_COLOR {0, 255, 255}
#define END_COLOR {214, 0, 110}
#define OPEN_COLOR {0, 255, 0}
#define CLOSED_COLOR {0, 0, 255}



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

	AStar(Canvas *_canvas) : startNode(NULL), 
							 endNode(NULL), 
							 path(NULL), 
							 canvas(_canvas)
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
	}

	virtual ~AStar()
	{
		if(startNode != NULL)
		{
			delete startNode;
			startNode = NULL;
		}

		if(endNode != NULL)
		{
			delete endNode;
			endNode = NULL;
		}

		if(path != NULL)
		{
			delete path;
			path = NULL;
		}

		if(canvas != NULL)
		{
			delete canvas;
			canvas = NULL;
		}
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

	void show()
	{
		if(this->canvas != NULL)
		{
			this->canvas->show();
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
		this->startNode->setGValue(0.0);
		this->startNode->setHValue(this->endNode);
		this->openSet.push_back(this->startNode);
		
		int currentNodeIdx = 0;
		mNode *currentNode = this->startNode;

		cout << "start node:" << endl;
		currentNode->print();

		while(this->openSet.size() > 0)
		{
			currentNodeIdx = this->getNodeWithLowestValue();
			currentNode = &this->canvas->grid->nodes[currentNodeIdx];
			(*this).removeFromOpenSet(currentNodeIdx);
			this->closedSet.push_back(currentNode);

			cout << "current node:" << endl;
			currentNode->print();		

			if(currentNode->compare(this->endNode))
			{
				cout << "end node was found!" << endl;
				break;
			}

			vector<mNode*> neighbors = this->canvas->grid->getNeighbors(currentNode->x, currentNode->y);
			for (int node = 0; node < neighbors.size(); node++)
			{
				cout << "neighbor " << node << ":" << endl;
				neighbors[node]->print();

				if(neighbors[node]->walkable or 
				   std::find(this->closedSet.begin(), this->closedSet.end(), neighbors[node]) != this->closedSet.end()) 
				{
					double newPath = currentNode->getFValue() + 1.0;
					std::vector<mNode*>::iterator findIdx;
					findIdx = std::find(this->openSet.begin(), this->openSet.end(), neighbors[node]);	
					if(findIdx != this->openSet.end() or
					   newPath < neighbors[node]->getFValue())
					{	
						cout << "evaluating neighbor " << node << endl;
						neighbors[node]->setPrevious(currentNode);
						neighbors[node]->setGValue(currentNode->gValue + 1.0);
						neighbors[node]->setHValue(this->endNode);
						neighbors[node]->print();

						if(findIdx != this->openSet.end()) 
							cout << "adding neighbor" << node << " to openSet" << endl;
							this->openSet.push_back(neighbors[node]);
					}
				}
			}

			(*this).draw();
			(*this).show();
		}
	}

	int getNodeWithLowestValue()
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

		return lowestIdx;
	}

	void removeFromOpenSet(int index)
	{
		int lastIndex = this->openSet.size() - 1;
		swap(this->openSet[lastIndex], this->openSet[index]);
		this->openSet.pop_back();
	}
};

#endif