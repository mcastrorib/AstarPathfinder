#ifndef SPHERICAL_PORE_DRAWER_H_
#define SPHERICAL_PORE_DRAWER_H_

// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>

// include base class file
#include "Pore.h"
#include "SphericalPore.h"
#include "SyntheticRock.h"

using namespace std;

class SphericalPoreDrawer
{
public:
    // image reference
    SyntheticRock &canvas;

    SphericalPoreDrawer(SyntheticRock &_image);
    virtual ~SphericalPoreDrawer(){};

    // Methods
    void insertSphericalLatticeArray(int _latticeEdge, double _sphereRadius, bool _overlap = true);

    void removeSphericalLatticeArray(int _latticeEdge, double _sphereRadius, bool _overlap = true);

    void insertSphericalPore(SphericalPore &_pore, bool _overlapp);

    bool placeNewSphericalPore(SphericalPore &_pore, bool _overlap);

    bool checkPorePixels(SphericalPore &_pore, bool _overlapp);

    void applyBorderRestrictions(int &_x, int &_y, int &_z);

    void drawSphericalPore(SphericalPore &_pore);

    void eraseSphericalPore(SphericalPore &_pore);

    private:
    uint randomUint(uint begin, uint end);
    int randomInt(int begin, int end);

};

#endif