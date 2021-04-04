#ifndef PLANE_BARRIER_DRAWER_H_
#define PLANE_BARRIER_DRAWER_H_

// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>

// include base class file
#include "Pore.h"
#include "SyntheticRock.h"

using namespace std;

class PlaneBarrierDrawer
{
public:
    // image reference
    SyntheticRock &canvas;

    PlaneBarrierDrawer(SyntheticRock &_image);
    virtual ~PlaneBarrierDrawer(){};

    // Methods
    void insertPlaneXY(uint _coordZ);

    void insertPlaneXZ(uint _coordY);

    void insertPlaneYZ(uint _coordX);


    private:
    uint randomize(uint begin, uint end);

};

#endif