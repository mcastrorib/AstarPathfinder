#ifndef CYLINDRICAL_PORE_H_
#define CYLINDRICAL_PORE_H_

// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>

// include base class file
#include "../Math/Vector3D.h"
#include "Pore.h"

using namespace std;

class CylindricalPore : public Pore
{
public:
    double centerX1, centerY1, centerZ1;
    double centerX2, centerY2, centerZ2;
    double radius;

private:
    Vector3D _axis;
    Vector3D _faceNormal;

public:

    // CylindricalPore methods:
    // constructors
    CylindricalPore(const Pore &pore);
    CylindricalPore(double centerX1, double centerY1, double centerZ1, 
                    double centerX2, double centerY2, double centerZ2, 
                    double radius);


    // copy constructor
    CylindricalPore(const CylindricalPore &otherPore);

    // default destructor
    virtual ~CylindricalPore()
    {
        // cout << "Cylindrical pore object destroyed succesfully" << endl;
    }

    double findPointDistanceToCenter1(double pointX, double pointY, double pointZ);
    double findPointDistanceToCenter2(double pointX, double pointY, double pointZ);
    double findPointDistanceToAxis(double pointX, double pointY, double pointZ);


    // set methods
    void setAxisVector();
    void setFaceNormalVector(void);
    void setFaceNormalVector(Vector3D face);
    void setType(){ this->type = "cylindrical"; }
    void setSize();
    void setDimensions();

    // get methods
    double getCenterX1(){ return this->centerX1; }
    double getCenterY1(){ return this->centerY1; }
    double getCenterZ1(){ return this->centerZ1; }
    double getCenterX2(){ return this->centerX2; }
    double getCenterY2(){ return this->centerY2; }
    double getCenterZ2(){ return this->centerZ2; }
    double getRadius(){ return this->radius; }
    Vector3D getAxis(){ return this->_axis; }
    double getAxisX(){ return this->_axis.getX(); }
    double getAxisY(){ return this->_axis.getY(); }
    double getAxisZ(){ return this->_axis.getZ(); }
    double getAxisNorm(){ return this->_axis.getNorm(); }
    Vector3D getFaceNormal(){ return this->_faceNormal; }
    double getFaceNormalX(){ return this->_faceNormal.getX(); }
    double getFaceNormalY(){ return this->_faceNormal.getY(); }
    double getFaceNormalZ(){ return this->_faceNormal.getZ(); }
    double getFaceNormalNorm(){ return this->_faceNormal.getNorm(); }
};

#endif