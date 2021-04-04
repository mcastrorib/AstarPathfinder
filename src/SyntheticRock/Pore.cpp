// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

// include header file
#include "Pore.h"

using namespace std;

// Pore methods
// default constructor
Pore::Pore() : x(0), y(0), z(0), size(0), type("none")
{
    this->dim_x = 0;
    this->dim_y = 0;
    this->dim_z = 0;
}

Pore::Pore(int _x, int _y, int _z) : x(_x), y(_y), z(_z), size(0), type("none")
{
    this->dim_x = 0;
    this->dim_y = 0;
    this->dim_z = 0;
}

// copy constructor
Pore::Pore(const Pore &_otherPore)
{
    // image attributes
    this->x = _otherPore.x;
    this->y = _otherPore.y;
    this->z = _otherPore.z;
    this->dim_x = _otherPore.dim_x;
    this->dim_y = _otherPore.dim_y;
    this->dim_z = _otherPore.dim_z;
    this->size = _otherPore.size;
    this->type = _otherPore.type;
}

void Pore::printInfo()
{
    cout << "x = " << (*this).getX() << endl;
    cout << "y = " << (*this).getY() << endl;
    cout << "z = " << (*this).getZ() << endl;
    cout << "dim x = " << (*this).getDimX() << endl;
    cout << "dim y = " << (*this).getDimY() << endl;
    cout << "dim z = " << (*this).getDimZ() << endl;
    cout << "size = " << (*this).getSize() << endl;
    cout << "type = " << (*this).getType() << endl;
}

string Pore::getInfo()
{
    string info;
    info = this->type + " " + std::to_string(this->size) + "\n";
    info = info + std::to_string(this->x) + " ";
    info = info + std::to_string(this->y) + " ";
    info = info + std::to_string(this->z) + "\n";

    return info;
}
