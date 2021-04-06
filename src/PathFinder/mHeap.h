#ifndef HEAP_H
#define HEAP_H

// include CMake Configuration file
#include "pathfinder_config.h"

// include other PathFinder classes
#include "mNode.h"

using namespace std;

class mHeap
{
public:
    int maxSize;
    int currentSize;
    mNode **heapNodes;

    mHeap(int maxSize) : currentSize(0)
    {
        this->heapNodes = new mNode*[maxSize];
    }

    virtual ~mHeap()
    {
        cout << "deleting heap..." << endl;
        if(this->heapNodes != NULL)
        {
            delete [] this->heapNodes;
            this->heapNodes = NULL;
        }
        cout << "deleting heap...Done" << endl;
    }

    void update(mNode *node)
    {
        (*this).sortUp(node->getHeapIndex());
    }

    bool contains(mNode *node)
    {   
        int nodeIdx = node->getHeapIndex();
        if(nodeIdx > -1 and nodeIdx < this->currentSize)
        {
            return node->compare(this->heapNodes[nodeIdx]);
        } else {
            return false;
        }

    }

    int size()
    {
        return this->currentSize;
    }

    void add(mNode * node)
    {
        node->setHeapIndex(currentSize);
        this->heapNodes[this->currentSize] = node;
        (*this).sortUp(this->currentSize);
        this->currentSize++;        
    }

    mNode* remove()
    {
        mNode *first = NULL;
        if(this->currentSize > 0)
        {
            first = this->heapNodes[0];
            this->currentSize--;
            this->swap(0, this->currentSize);
            this->sortDown(0);
            first->setHeapIndex(-1);
        }        
        return first;
    }

    void swap(int idxA, int idxB)
    {
        // swap heap indexes
        this->heapNodes[idxA]->setHeapIndex(idxB);
        this->heapNodes[idxB]->setHeapIndex(idxA);
        
        // swap heap positions
        mNode *temp = this->heapNodes[idxA];
        this->heapNodes[idxA] = this->heapNodes[idxB];
        this->heapNodes[idxB] = temp;
    }

    void sortUp(int idx)
    {   
        int currentIdx = idx;
        int parentIdx;
        while(true)
        {
            parentIdx = (currentIdx - 1) / 2;
            if(this->heapNodes[currentIdx]->isGreater(this->heapNodes[parentIdx]) < 0)
            {
                this->swap(currentIdx, parentIdx);
                currentIdx = parentIdx;
            } else
            {
                return;
            }
        }
    }

    void sortDown(int idx)
    {   
        int currentIdx = idx;
        int LeftChildIdx = idx;
        int RightChildIdx = idx;

        while(true)
        {
            int LeftChildIdx = 2*currentIdx + 1;
            int RightChildIdx = 2*currentIdx + 2;
            int bestChildIdx = LeftChildIdx;
            if(RightChildIdx < this->currentSize and 
               this->heapNodes[RightChildIdx]->isGreater(this->heapNodes[LeftChildIdx]) < 0)
            {
                bestChildIdx = RightChildIdx;
            }

            if(bestChildIdx < this->currentSize and
               this->heapNodes[currentIdx]->isGreater(this->heapNodes[bestChildIdx]) > 0)
            {
                this->swap(currentIdx, bestChildIdx);
                currentIdx = bestChildIdx;
            } else 
            {
                return;
            }
        }
    }

    void print()
    {
        for(int i = 0; i < this->currentSize; i++)
        {
            cout << "heap " << i << endl;
            this->heapNodes[i]->print();
        }
    }

};




#endif 