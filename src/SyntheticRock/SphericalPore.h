#ifndef SPHERICAL_PORE_H_
#define SPHERICAL_PORE_H_

// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>

// include base class file
#include "Pore.h"
using namespace std;


class SphericalPore : public Pore
{
public:
    double centerX, centerY, centerZ;
    double radius;
    int cubeX, cubeY, cubeZ;
    uint cubeDim;

    // SphericalPore methods:
    // constructors
    SphericalPore(const Pore &_pore);
    SphericalPore(double _centerX, double _centerY, double _centerZ, double _radius);


    // copy constructor
    SphericalPore(const SphericalPore &_otherPore);

    // default destructor
    virtual ~SphericalPore()
    {
        // cout << "Spherical pore object destroyed succesfully" << endl;
    }

    double findPointDistanceToCenter(double _pointX, double _pointY, double _pointZ);

    // set methods
    void setType(){ this->type = "spherical"; }
    void setCube();
    void setSize();

    // get methods
    double getCenterX(){ return this->centerX; }
    double getCenterY(){ return this->centerY; }
    double getCenterZ(){ return this->centerZ; }
    double getRadius(){ return this->radius; }
    int getCubeX(){ return this->cubeX; }
    int getCubeY(){ return this->cubeY; }
    int getCubeZ(){ return this->cubeZ; }
    uint getCubeDim(){ return this->cubeDim; }
};

#endif