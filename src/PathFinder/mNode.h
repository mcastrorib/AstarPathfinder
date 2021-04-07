#ifndef NODE_H
#define NODE_H

// include Configuration file
#include "PathFinder.h"

using namespace std;

class mNode
{
public:
	int x;
	int y;
	bool walkable;
	double gValue;
	double hValue;
	mNode *previous;
	int heapIndex;
	
	mNode() : x(-1), 
			  y(-1), 
			  walkable(false), 
			  previous(NULL), 
			  gValue(DBL_MAX), 
			  hValue(DBL_MAX),
			  heapIndex(-1)
	{}

	mNode(int _x, int _y, bool _walkable=true) : x(_x), 
												 y(_y), 
												 walkable(_walkable), 
												 previous(NULL), 
												 gValue(DBL_MAX), 
												 hValue(DBL_MAX),
												 heapIndex(-1)	
	{}

	mNode(const mNode &_otheNode)
	{
		this->x = _otheNode.x;
		this->y = _otheNode.y;
		this->walkable = _otheNode.walkable;
		this->gValue = _otheNode.gValue;
		this->hValue = _otheNode.hValue;
		this->previous = _otheNode.previous;
		this->heapIndex = _otheNode.heapIndex;

	}

	virtual ~mNode(){}

	bool compare(mNode *node)
	{
		if(this->x == node->x and this->y == node->y)
			return true;
		else
			return false;
	}

	int isGreater(mNode *node)
	{
		if(node->getFValue() < this->getFValue())
		{
			return 1;
		} else if(node->getFValue() == this->getFValue())
		{
			if(node->getHValue() < this->getHValue())
			{
				return 1;
			} else if(node->getHValue() == this->getHValue())
			{
				return 0;
			}
		}

		return -1;
	}

	void set(int _x, int _y, bool _walkable=true)
	{
		this->x = _x;
		this->y = _y;
		this->walkable = _walkable;
	}
	
	void print()
	{
		cout << "x:" << this->x << " ";
		cout << "y:" << this->y << " ";
		if(this->walkable) cout << "walkable: true" << endl;
		else cout << "walkable: false" << endl; 
		cout << "g = " << this->gValue << ", ";
		cout << "h = " << this->hValue << ", ";
		cout << "f = " << (*this).getFValue() << endl;
		cout << "heapIdx = " << (*this).getHeapIndex() << endl << endl;
	}

	void setPrevious(mNode *node)
	{
		this->previous = node;
	}

	mNode * getPrevious()
	{
		return this->previous;
	}

	void setGValue(double _val)
	{
		this->gValue = _val;
	}

	double getGValue()
	{
		return this->gValue;
	}

	void setHValue(double _newH)
	{
		this->hValue = _newH;
	}

	double getHValue()
	{
		return this->hValue;
	}

	double getFValue()
	{
		return this->gValue + this->hValue;
	}

	void setHeapIndex(int _index)
	{
		this->heapIndex = _index;
	}

	int getHeapIndex()
	{
		return this->heapIndex;
	}
};

#endif