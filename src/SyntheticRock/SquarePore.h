#ifndef SQUARE_PORES_H_
#define SQUARE_PORES_H_

// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>

// include base class file
#include "Pore.h"

// define pore family sizes
#ifndef PORE_SIZES
#define BIG_PORE_SIZE 30
#define MEDIUM_PORE_SIZE 10
#define SMALL_PORE_SIZE 2
#endif

using namespace std;

class SquarePore : public Pore
{
public:
    uint length;
    string family;

    // SquarePore methods:
    // constructors
    SquarePore();
    SquarePore(const Pore &_pore);
    SquarePore(uint _length, int _x = 0, int _y = 0, int _z = 0);
    SquarePore(string _family, int _x = 0, int _y = 0, int _z = 0);

    // copy constructor
    SquarePore(const SquarePore &_otherPore);

    // default destructor
    virtual ~SquarePore()
    {
        // cout << "Square pore object destroyed succesfully" << endl;
    }

    // set methods
    void setFamily();
    void setFamily(string _family);
    void setLength();
    void setLength(uint _length);
    void setLength(const Pore &_pore);
    void setSize();
    void setType();

    // get methods
    inline uint getLength() { return this->length; }
    inline string getFamily() { return this->family; }

    // print info
    void printInfo();
};

#endif