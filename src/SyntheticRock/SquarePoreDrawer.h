#ifndef SQUARE_PORE_DRAWER_H_
#define SQUARE_PORE_DRAWER_H_

// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>

// include base class file
#include "Pore.h"
#include "SyntheticRock.h"

using namespace std;

class SquarePoreDrawer
{
public:
    // image reference
    SyntheticRock &canvas;

    SquarePoreDrawer(SyntheticRock &_image);
    virtual ~SquarePoreDrawer(){};

    // Methods
    void insertSquarePores(uint _quantity, string _family);

    SquarePore createNewSquarePore(string _family);

    bool placeNewSquarePore(SquarePore &_pore);

    bool checkNeighborPixels(int _x, int _y);

    void applyBorderRestrictions(int &_x, int &_y);

    void drawSquarePore(SquarePore &_pore);

    void eraseSquarePore(SquarePore &_pore);

    void eraseRoughnessInPore(SquarePore &_pore);

    void removeLastPore();

    void removeFamilyOfPores(string _family);

    void applyRoughness();

    void applyRoughness(string _family);

    void removeRoughness();

    void removeRoughness(string _family);

    void applyVerticalRoughness(SquarePore &_pore);

    void createVerticalRoughness(int _y, int _x1, int _x2);

    void applyHorizontalRoughness(SquarePore &_pore);

    void createHorizontalRoughness(int _x, int _y1, int _y2);

    private:
    uint randomize(uint begin, uint end);

};

#endif