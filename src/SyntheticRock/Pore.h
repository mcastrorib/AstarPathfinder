#ifndef PORES_H_
#define PORES_H_

// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Pore
{
public:
    // pore position
    int x;
    int y;
    int z;

    uint dim_x;
    uint dim_y;
    uint dim_z;    

    uint size;
    string type;

    // Pore methods:
    // default constructors
    Pore();
    Pore(int _x, int _y, int _z = 0);

    //copy constructors
    Pore(const Pore &_otherPore);

    // default destructor
    virtual ~Pore()
    {
        // cout << "Pore object destroyed succesfully" << endl;
    }

    // set methods
    void setX(int _x) { this->x = _x; }
    void setY(int _y) { this->y = _y; }
    void setZ(int _z) { this->z = _z; }
    void setDimX(uint _dim_x) { this->dim_x = _dim_x; }
    void setDimY(uint _dim_y) { this->dim_y = _dim_y; }
    void setDimZ(uint _dim_z) { this->dim_z = _dim_z; }
    void setType(string _type) { this->type = _type; }
    void setSize()
    {
        this->size = this->dim_x * this->dim_y * this->dim_z;
    }

    // get methods
    int getX() const { return this->x; }
    int getY() const { return this->y; }
    int getZ() const { return this->z; }
    uint getDimX() const { return this->dim_x; }
    uint getDimY() const { return this->dim_y; }
    uint getDimZ() const { return this->dim_z; }
    uint getSize() const { return this->size; }
    string getType() const { return this->type; }

    void printInfo();
    string getInfo();
};

#endif