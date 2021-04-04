// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

// include header file
#include "PrismaticPore.h"

using namespace std;

// PrismaticPore methods:
// constructors
PrismaticPore::PrismaticPore(const Pore &_pore) : Pore(_pore)
{
    (*this).setType();
    (*this).setSize();
}

PrismaticPore::PrismaticPore(uint _dim_x, 
                             uint _dim_y, 
                             uint _dim_z, 
                             int _x, 
                             int _y, 
                             int _z) : Pore(_x, _y, _z)
{
    (*this).setDimX(_dim_x);
    (*this).setDimY(_dim_y);
    (*this).setDimZ(_dim_z);
    (*this).setType();
    (*this).setSize();
}

// copy constructor
PrismaticPore::PrismaticPore(const PrismaticPore &_otherPore)
{
    this->x = _otherPore.x;
    this->y = _otherPore.y;
    this->z = _otherPore.z;
    this->dim_x = _otherPore.x;
    this->dim_y = _otherPore.y;
    this->dim_z = _otherPore.z;
    this->size = _otherPore.size;
    this->type = _otherPore.type;
}

// methods
void PrismaticPore::setType()
{
    this->type = "prismatic";
}