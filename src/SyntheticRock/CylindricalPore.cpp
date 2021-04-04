// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// include header file
#include "../Math/Vector3D.h"
#include "CylindricalPore.h"


using namespace std;

// SphericalPore methods:
// constructors
CylindricalPore::CylindricalPore(const Pore &_pore) : Pore(_pore)
{
    (*this).setType();
}

CylindricalPore::CylindricalPore(double _centerX1, double _centerY1, double _centerZ1,
                                 double _centerX2, double _centerY2, double _centerZ2,
                                 double _radius) : Pore(0,0,0),
                                                   centerX1(_centerX1),
                                                   centerY1(_centerY1),
                                                   centerZ1(_centerZ1),
                                                   centerX2(_centerX2),
                                                   centerY2(_centerY2),
                                                   centerZ2(_centerZ2),
                                                   radius(_radius)
{
    (*this).setAxisVector();
    (*this).setFaceNormalVector();
    (*this).setDimensions();
    (*this).setType();
    (*this).setSize();
}

// copy constructor
CylindricalPore::CylindricalPore(const CylindricalPore &_otherPore)
{
    this->centerX1 = _otherPore.centerX1;
    this->centerY1 = _otherPore.centerY1;
    this->centerZ1 = _otherPore.centerZ1;
    this->centerX2 = _otherPore.centerX2;
    this->centerY2 = _otherPore.centerY2;
    this->centerZ2 = _otherPore.centerZ2;
    this->radius = _otherPore.radius;

    this->x = _otherPore.x;
    this->y = _otherPore.y;
    this->z = _otherPore.z;
    this->dim_x = _otherPore.dim_x;
    this->dim_y = _otherPore.dim_y;
    this->dim_z = _otherPore.dim_z;
    this->size = _otherPore.size;
    this->type = _otherPore.type;
}

void CylindricalPore::setAxisVector()
{
    this->_axis.setX((*this).getCenterX2() - (*this).getCenterX1());
    this->_axis.setY((*this).getCenterY2() - (*this).getCenterY1());
    this->_axis.setZ((*this).getCenterZ2() - (*this).getCenterZ1());
}

/*
By default, cylinder face is perpendicular to axis z
*/
void CylindricalPore::setFaceNormalVector(void)
{
    this->_faceNormal.setX(0.0);
    this->_faceNormal.setY(0.0);
    this->_faceNormal.setZ(0.0);   

    Vector3D ei(1,0,0);
    Vector3D ej(0,1,0);
    Vector3D ek(0,0,1);
    Vector3D axis((*this).getAxis());
    
    if(axis.dotProduct(ei) > 0.0)
    {
        this->_faceNormal.setX(1.0);
    }

    if(axis.dotProduct(ej) > 0.0)
    {
        this->_faceNormal.setY(1.0);
    } 

    if(axis.dotProduct(ek) > 0.0)
    {
        this->_faceNormal.setZ(1.0);
    } 
}

void CylindricalPore::setFaceNormalVector(Vector3D _face)
{
    this->_faceNormal.setX(_face.getX());
    this->_faceNormal.setY(_face.getY());
    this->_faceNormal.setZ(_face.getZ());   
}

// precisa ser refeito!!!
void CylindricalPore::setSize()
{
    Vector3D ei(1,0,0);
    Vector3D ej(0,1,0);
    Vector3D ek(0,0,1);
    Vector3D normal((*this).getFaceNormal());
    
    // treat face normal to x axis
    if(normal.dotProduct(ei) > 0.0)
    {
        cout << "face is normal to x axis" << endl;
    }

    // treat face normal to x axis
    if(normal.dotProduct(ej) > 0.0)
    {
        cout << "face is normal to y axis" << endl;
    } 

    // treat face normal to x axis
    if(normal.dotProduct(ek) > 0.0)
    {
        cout << "face is normal to z axis" << endl;
    }
} 

void CylindricalPore::setDimensions()
{
    // by default, cylinder face is in z plane
    (*this).setX(floor((*this).getCenterX1() - (*this).getRadius()));
    (*this).setY(floor((*this).getCenterY1() - (*this).getRadius()));
    (*this).setZ(floor((*this).getCenterZ1() - (*this).getRadius()));
    (*this).setDimX((*this).getRadius());
    (*this).setDimY((*this).getRadius());
    (*this).setDimZ((*this).getRadius());

    Vector3D ei(1,0,0);
    Vector3D ej(0,1,0);
    Vector3D ek(0,0,1);
    Vector3D normal((*this).getFaceNormal());
    
    // treat face normal to x axis
    if(normal.dotProduct(ei) > 0.0)
    {
        (*this).setX((*this).getCenterX1());
        (*this).setDimX((*this).getAxisX());
    }

    if(normal.dotProduct(ej) > 0.0)
    {
        (*this).setY((*this).getCenterY1());
        (*this).setDimY((*this).getAxisY());
    } 

    if(normal.dotProduct(ek) > 0.0)
    {
        (*this).setZ((*this).getCenterZ1());
        (*this).setDimZ((*this).getAxisZ());
    }
}

double CylindricalPore::findPointDistanceToCenter1(double _pointX, double _pointY, double _pointZ)
{
    Vector3D distance;
    distance.setX(_pointX - (*this).getCenterX1());
    distance.setY(_pointY - (*this).getCenterY1());
    distance.setZ(_pointZ - (*this).getCenterZ1());
    distance.setNorm();

    return (distance.getNorm());
}

double CylindricalPore::findPointDistanceToCenter2(double _pointX, double _pointY, double _pointZ)
{
    Vector3D distance;
    distance.setX(_pointX - (*this).getCenterX2());
    distance.setY(_pointY - (*this).getCenterY2());
    distance.setZ(_pointZ - (*this).getCenterZ2());
    distance.setNorm();

    return (distance.getNorm());
}

double CylindricalPore::findPointDistanceToAxis(double _pointX, double _pointY, double _pointZ)
{
    // set vector from center to point
    Vector3D P1P0;
    P1P0.setX(_pointX - (*this).getCenterX1());
    P1P0.setY(_pointY - (*this).getCenterY1());
    P1P0.setZ(_pointZ - (*this).getCenterZ1());

    // set axis vector 
    Vector3D axisCopy;
    axisCopy = (*this).getAxis();

    // get axis vector norm
    double axisNorm = axisCopy.getNorm();


    // apply cross product with P1P0    
    axisCopy.crossProduct(P1P0);
    
    
    // return point distance to center
    return (axisCopy.getNorm()/axisNorm);
}


