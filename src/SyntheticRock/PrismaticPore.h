#ifndef PRISMATIC_PORE_H_
#define PRISMATIC_PORE_H_

// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>

// include base class file
#include "Pore.h"
using namespace std;

struct PrismaticPoreFamily
{
    uint minDimX;
    uint maxDimX;
    uint minDimY;
    uint maxDimY;
    uint minDimZ;
    uint maxDimZ;
};

class PrismaticPore : public Pore
{
public:
    // PrismaticPore methods:
    // constructors
    PrismaticPore(const Pore &_pore);
    PrismaticPore(uint _dim_x = 0, uint _dim_y = 0, uint _dim_z = 0, int _x = 0, int _y = 0, int _z = 0);


    // copy constructor
    PrismaticPore(const PrismaticPore &_otherPore);

    // default destructor
    virtual ~PrismaticPore()
    {
        // cout << "Prismatic pore object destroyed succesfully" << endl;
    }

    // set methods
    void setType();
};

#endif