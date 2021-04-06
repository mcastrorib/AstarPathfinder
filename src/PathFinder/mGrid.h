#ifndef GRID_H
#define GRID_H

// include Astar Configuration file
#include "pathfinder_config.h"

// include other PathFinder classes

using namespace std;
#include "mNode.h"

using namespace std;

class mGrid
{
public:
	int gridSize;
	int gridDimX;
	int gridDimY;
	mNode *nodes;
	int connectivity;

	mGrid(int _dimX, int _dimY) : gridDimX(_dimX), gridDimY(_dimY), gridSize(_dimX*_dimY), connectivity(4)
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
		this->connectivity = otherGrid.connectivity;
	}

	virtual ~mGrid()
	{
		cout << "deleting grid..." << endl;
		if(nodes != NULL)
		{
			delete [] nodes;
			nodes = NULL;
		}
		cout << "deleting grid...Done" << endl;
	}

	int getNodeIdx(int x, int y)
	{
		int index = this->gridDimX * y + x;
		index = index % gridSize;
		return index;
	}

	mNode * getNode(int x, int y)
	{
		return &this->nodes[getNodeIdx(x,y)];
	}

	void setConnectivity(int _connectivity)
	{
		if(_connectivity == 4) 
		{ 
			this->connectivity = _connectivity;
		} else
		if(_connectivity == 8) 
		{
			this->connectivity = _connectivity;
		} else
		{
			cout << "Assigned connectivity is not valid (only accept 4 or 8)." << endl;
			cout << "Current connectivity is " << this->connectivity << endl;
		}
	}

	vector<mNode *> getConnectedNeighbors(int _x, int _y)
	{
		if(this->connectivity == 4) 
		{
				return this->getConnectedNeighbors_4n(_x, _y);
		}
		else if (this->connectivity == 8) 
		{
			return this->getConnectedNeighbors_8n(_x, _y);
		}
		else
		{
			vector<mNode *> emptyNeighbors(0);
			return emptyNeighbors;
		}	
		
	}

	vector<mNode *> getConnectedNeighbors_4n(int _x, int _y)
	{
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

	vector<mNode *> getConnectedNeighbors_8n(int _x, int _y)
	{
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

		// get diagonal neighbors
		if(_x-1 >= 0 and _y-1 >= 0)
		{
			index = (*this).getNodeIdx(_x-1, _y-1);
			if(this->nodes[index].walkable) neighbors.push_back(&this->nodes[index]);
		}

		if(_x-1 >= 0 and _y+1 < this->gridDimY)
		{
			index = (*this).getNodeIdx(_x-1, _y+1);
			if(this->nodes[index].walkable) neighbors.push_back(&this->nodes[index]);
		}

		if(_x+1 < this->gridDimX and _y-1 >= 0)
		{
			index = (*this).getNodeIdx(_x+1, _y-1);
			if(this->nodes[index].walkable) neighbors.push_back(&this->nodes[index]);
		}

		if(_x+1 < this->gridDimX and _y+1 < this->gridDimY)
		{
			index = (*this).getNodeIdx(_x+1, _y+1);
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