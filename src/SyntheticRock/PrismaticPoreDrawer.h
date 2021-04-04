#ifndef PRISMATIC_PORE_DRAWER_H_
#define PRISMATIC_PORE_DRAWER_H_

// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>

// include base class file
#include "Pore.h"
#include "PrismaticPore.h"
#include "SyntheticRock.h"

using namespace std;

class PrismaticPoreDrawer
{
public:
    // image reference
    SyntheticRock &canvas;

    PrismaticPoreDrawer(SyntheticRock &_image);
    virtual ~PrismaticPoreDrawer(){};

    // Methods
    void insertPrismaticPores(PrismaticPoreFamily _family, double porosity);

    PrismaticPore createNewPrismaticPore(PrismaticPoreFamily _family);

    bool placeNewPrismaticPore(PrismaticPore &_pore);

    bool checkPorePixels(PrismaticPore &_pore);

    void applyBorderRestrictions(int &_x, int &_y, int &_z);

    void drawPrismaticPore(PrismaticPore &_pore);

    void erasePrismaticPore(PrismaticPore &_pore);

    void eraseRoughnessInPore(PrismaticPore &_pore);

    void removeLastPore();

    void removeFamilyOfPores(PrismaticPoreFamily _family);

    void removePoresInSizeInterval(uint _maxsize, uint _minsize);

    void applyRoughness();

    void applyRoughness(PrismaticPoreFamily _family);

    void removeRoughness();

    void removeRoughness(PrismaticPoreFamily _family);

    void applyVerticalRoughness(PrismaticPore &_pore);

    void createVerticalRoughness(int _y, int _x1, int _x2, int _z);

    void applyHorizontalRoughness(PrismaticPore &_pore);

    void createHorizontalRoughness(int _x, int _y1, int _y2, int _z);

    private:
    uint randomUint(uint begin, uint end);
    int randomInt(int begin, int end);

};

#endif