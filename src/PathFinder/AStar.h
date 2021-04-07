#ifndef ASTAR_H
#define ASTAR_H

// include Configuration file
#include "PathFinder.h"

using namespace std;

class AStar
{
public:
	mNode *startNode;
	mNode *endNode;
	mNode *path;
	Canvas *canvas;
	mHeap *openSet;
	map<mNode *, int> closedSet;
	bool visualize;
	int visualTimeRate;
	bool drawOpenSet;
	bool drawClosedSet;
	

	AStar(int _x, int _y) :  startNode(NULL), 
							 endNode(NULL), 
							 path(NULL),
							 openSet(NULL),
							 drawOpenSet(true),
							 drawClosedSet(true),
							 visualize(false),
							 visualTimeRate(0)
	{		
		this->canvas = new Canvas(_x, _y);
		map<mNode*, int> closedSet();
		(*this).drawGridNodes();
	}

	AStar(Canvas *_canvas) : startNode(NULL), 
							 endNode(NULL), 
							 path(NULL), 
							 openSet(NULL),
							 canvas(_canvas),
							 drawOpenSet(true),
							 drawClosedSet(true),
							 visualize(false),
							 visualTimeRate(0)
	{		
		map<mNode*, int> closedSet();
		(*this).drawGridNodes();
	}

	AStar(mGrid *_grid) : startNode(NULL), 
						  endNode(NULL), 
						  path(NULL), 
						  openSet(NULL),
						  drawOpenSet(true),
						  drawClosedSet(true),
						  visualize(false),
						  visualTimeRate(0)
	{		
		this->canvas = new Canvas(_grid);
		map<mNode*, int> closedSet();
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
		this->visualTimeRate = _other.visualTimeRate;
		this->drawOpenSet = _other.drawOpenSet;
		this->drawClosedSet = _other.drawClosedSet;
	}

	virtual ~AStar()
	{
		cout << "deleting Astar..." << endl;
		
		this->startNode = NULL;
		this->endNode = NULL;
		this->path = NULL;

		if(this->openSet != NULL)
		{
			delete this->openSet;
			this->openSet = NULL;
		}

		if(this->canvas != NULL)
		{
			delete this->canvas;
			this->canvas = NULL;
		}



		cout << "deleting Astar...Done" << endl;
	}

	void setGridConnectivity(int con)
	{
		this->canvas->grid->setConnectivity(con);
	}

	void setDrawOpenSet(bool _b)
	{
		this->drawOpenSet = _b;
	}

	void setDrawClosedSet(bool _b)
	{
		this->drawClosedSet = _b;
	}

	void setVisualization(bool b=true, int time=0)
	{
		this->visualize = b;
		this->visualTimeRate = time;
	}

	void getStartNode()
	{
		vector<int> Pos = this->canvas->getMousePosition("Select start position: ");
		(*this).setStartNode(Pos[0], Pos[1]);
	}

	void setStartNode(int x, int y)
	{
		int index = this->canvas->grid->getNodeIdx(x,y);
		if(this->canvas->grid->nodes[index].walkable)
			this->startNode = &this->canvas->grid->nodes[index];		
	}

	void getEndNode()
	{
		vector<int> Pos = this->canvas->getMousePosition("Select end position: ");
		(*this).setEndNode(Pos[0], Pos[1]);
	}

	void setEndNode(int x, int y)
	{
		int index = this->canvas->grid->getNodeIdx(x,y);	
		if(this->canvas->grid->nodes[index].walkable)
			this->endNode = &this->canvas->grid->nodes[index];
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
		mNode *currentNode;
		int posX, posY;

		if(this->openSet != NULL and this->openSet->size() > 0)
		{
			cv::Scalar color;
			if(this->drawOpenSet) color = OPEN_COLOR;
			else color = FREE_COLOR;
			
			for (int node = 0; node < this->openSet->size(); node++)
			{
				int currentNodeX = this->openSet->heapNodes[node]->x;
				int currentNodeY = this->openSet->heapNodes[node]->y;
				posX = currentNodeX * this->canvas->nodeSizeX + currentNodeX * this->canvas->gridLinewidth;
				posY = currentNodeY * this->canvas->nodeSizeY + currentNodeY * this->canvas->gridLinewidth;
				this->canvas->drawRectangle(posX, posY, color, this->canvas->nodeSizeX, this->canvas->nodeSizeY);
			}
		}

		if(this->closedSet.size() > 0)
		{
			cv::Scalar color;
			if(this->drawClosedSet) color = CLOSED_COLOR;
			else color = FREE_COLOR;
			
			map<mNode*, int>::const_iterator it;
			for(it = this->closedSet.begin(); it != closedSet.end(); it++)
			{
				currentNode = it->first;
				int currentNodeX = currentNode->x;
				int currentNodeY = currentNode->y;
				posX = currentNodeX * this->canvas->nodeSizeX + currentNodeX * this->canvas->gridLinewidth;
				posY = currentNodeY * this->canvas->nodeSizeY + currentNodeY * this->canvas->gridLinewidth;
				this->canvas->drawRectangle(posX, posY, color, this->canvas->nodeSizeX, this->canvas->nodeSizeY);
			}
		}

		// draw current best path
		currentNode = this->path;
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
				mNode *node = this->canvas->grid->getNode(i,j);	
				if(node->walkable)
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
		if(this->startNode == NULL or this->endNode == NULL)
		{
			cout << "start and/or end nodes not set." << endl;
			return;
		}

		double stime = omp_get_wtime();
		cout << "starting findPath() method..." << endl;
		
		this->startNode->setGValue(0.0);
		(*this).applyHeuristic(this->startNode); //->setHValue(this->endNode);
		this->openSet = new mHeap(this->canvas->grid->gridSize);
		this->openSet->add(this->startNode);
		mNode *currentNode = this->startNode;
		this->path = currentNode;
		int iter = 0;

		while(this->openSet->size() > 0)
		{
			iter++;
			if(iter % 100 == 0) cout << "iter: " << iter << endl;			
			currentNode = this->openSet->remove();
			this->closedSet.insert(pair<mNode*, int>(currentNode, iter-1));
			this->path = currentNode;

			// Stop if destination node is reached
			if(currentNode->compare(this->endNode))
			{
				this->path = this->endNode;
				break;
			}

			// Get connected neighbors of current node and compare them 
			vector<mNode*> neighbors = this->canvas->grid->getConnectedNeighbors(currentNode->x, currentNode->y);
			double currentGValue = currentNode->getGValue();
			double currentHValue = currentNode->getHValue();
			double currentFValue = currentNode->getFValue();			
			for (int node = 0; node < neighbors.size(); node++)
			{
				// Check if neighbors is already in closed set
				bool closedSetContainsNode;
				if(this->closedSet.find(neighbors[node]) != this->closedSet.end())
				{ 
					closedSetContainsNode = true; 
				} else 
					closedSetContainsNode = false;
				
				// if neighbor is not closed, evaluate new path to neighbor 
				if(!closedSetContainsNode) 
				{
					double distanceToCurrent = (*this).EuclideanDistance(currentNode, neighbors[node]);
					double newPath = currentFValue + distanceToCurrent;
					
					bool openSetContainsNode = this->openSet->contains(neighbors[node]);					
					if(newPath < neighbors[node]->getFValue() or !openSetContainsNode)
					{	
						neighbors[node]->setPrevious(currentNode);
						neighbors[node]->setGValue(currentGValue + distanceToCurrent);
												
						if(!openSetContainsNode) 
						{
							(*this).applyHeuristic(neighbors[node]);
							this->openSet->add(neighbors[node]);
						}
						else
							this->openSet->update(neighbors[node]);
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
			cout << "path from start to end node was found :)" << endl << "length: " << this->path->getFValue() << endl;
		else 
			cout << "no path found :(" << endl;
		
		// draw last stage
		(*this).draw();
		(*this).show();
	}

	void applyHeuristic(mNode *current)
	{
		current->setHValue(heuristicFunction(current, this->endNode));
	}

	double heuristicFunction(mNode *nodeA, mNode *nodeB)
	{
		return EuclideanDistance(nodeA, nodeB);
	}

	double EuclideanDistance(mNode *nodeA, mNode *nodeB)
	{
		double dx = nodeA->x - nodeB->x;
		double dy = nodeA->y - nodeB->y;

		return sqrt(dx*dx + dy*dy);	
	
	}

	double EuclideanDistance(double dx, double dy)
	{
		return sqrt(dx*dx + dy*dy);	
	}

	double ManhatannDistance(mNode *nodeA, mNode *nodeB)
	{
		double dx = nodeA->x - nodeB->x;
		double dy = nodeA->y - nodeB->y;

		return (dx + dy);	
	}

	double ManhatannDistance(double dx, double dy)
	{
		return (dx + dy);		
	}
};

#endif