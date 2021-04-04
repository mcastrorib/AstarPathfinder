// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

// include header file
#include "SquarePore.h"

using namespace std;

// SquarePore methods:
// constructors
SquarePore::SquarePore() : Pore(0, 0, 0)
{
    (*this).setLength(1);
    (*this).setFamily();
    (*this).setSize();
    (*this).setType();
}

SquarePore::SquarePore(const Pore &_pore) : Pore(_pore)
{
    (*this).setLength(_pore);
    (*this).setFamily();
    (*this).setType();
}

SquarePore::SquarePore(uint _length, int _x, int _y, int _z) : Pore(_x, _y, _z), length(_length)
{
    (*this).setFamily();
    (*this).setSize();
    (*this).setType();
}

SquarePore::SquarePore(string _family, int _x, int _y, int _z) : Pore(_x, _y, _z), family(_family)
{
    (*this).setLength();
    (*this).setSize();
    (*this).setType();
}

// copy constructor
SquarePore::SquarePore(const SquarePore &_otherPore)
{
    this->x = _otherPore.x;
    this->y = _otherPore.y;
    this->z = _otherPore.z;
    this->size = _otherPore.size;
    this->type = _otherPore.type;

    this->length = _otherPore.length;
    this->family = _otherPore.family;
}

// methods
void SquarePore::setFamily()
{
    if (this->length < MEDIUM_PORE_SIZE)
    {
        this->family = "small";
    }
    else if (this->length < BIG_PORE_SIZE)
    {
        this->family = "medium";
    }
    else
    {
        this->family = "big";
    }
}
void SquarePore::setFamily(string _family)
{
    this->family = _family;
    (*this).setLength();
}

void SquarePore::setLength()
{
    if (this->family == "big")
    {
        this->length = BIG_PORE_SIZE;
    }
    else if (this->family == "medium")
    {
        this->length = MEDIUM_PORE_SIZE;
    }
    else
    {
        this->length = SMALL_PORE_SIZE;
    }
}

void SquarePore::setLength(uint _length)
{
    this->length = _length;
    (*this).setFamily();
}

void SquarePore::setLength(const Pore &_pore)
{
    this->length = sqrt(_pore.size);
}

void SquarePore::setSize()
{
    this->size = this->length * this->length;
}

void SquarePore::setType()
{
    this->type = "square";
}

void SquarePore::printInfo()
{
    (*this).Pore::printInfo();
    cout << "length = " << this->length << endl;
    cout << "family = " << this->family << endl;
}