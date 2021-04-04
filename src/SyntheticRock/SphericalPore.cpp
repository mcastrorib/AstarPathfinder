// include C++ standard libraries
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// include header file
#include "SphericalPore.h"

using namespace std;

// SphericalPore methods:
// constructors
SphericalPore::SphericalPore(const Pore &_pore) : Pore(_pore)
{
    (*this).setType();
    (*this).setSize();
}

SphericalPore::SphericalPore(double _centerX,
                             double _centerY,
                             double _centerZ,
                             double _radius) : Pore(0,0,0),
                                               centerX(_centerX),
                                               centerY(_centerY),
                                               centerZ(_centerZ),
                                               radius(_radius)
{
    (*this).setCube();
    (*this).setX((*this).getCubeX());
    (*this).setY((*this).getCubeY());
    (*this).setZ((*this).getCubeZ());
    (*this).setDimX((*this).getCubeDim());
    (*this).setDimY((*this).getCubeDim());
    (*this).setDimZ((*this).getCubeDim());
    (*this).setType();
    (*this).setSize();
}

// copy constructor
SphericalPore::SphericalPore(const SphericalPore &_otherPore)
{
    this->centerX = _otherPore.centerX;
    this->centerY = _otherPore.centerY;
    this->centerZ = _otherPore.centerZ;
    this->radius = _otherPore.radius;
    this->cubeX = _otherPore.cubeX;
    this->cubeY = _otherPore.cubeY;
    this->cubeZ = _otherPore.cubeZ;
    this->cubeDim = _otherPore.cubeDim;
    this->x = _otherPore.x;
    this->y = _otherPore.y;
    this->z = _otherPore.z;
    this->dim_x = _otherPore.x;
    this->dim_y = _otherPore.y;
    this->dim_z = _otherPore.z;
    this->size = _otherPore.size;
    this->type = _otherPore.type;
}

void SphericalPore::setCube()
{
    double minX = floor(this->centerX - this->radius);
    double maxX = ceil(this->centerX + this->radius);
    double minY = floor(this->centerY - this->radius);
    double maxY = ceil(this->centerY + this->radius);
    double minZ = floor(this->centerZ - this->radius);
    double maxZ = ceil(this->centerZ + this->radius);

    this->cubeX = (int) minX;
    this->cubeY = (int) minY;
    this->cubeZ = (int) minZ;
    this->cubeDim = (uint) fabs(maxX - minX);
}

void SphericalPore::setSize()
{
    int sizeIncrement = 0;
    int xBegin = (*this).getCubeX();
    int xEnd = xBegin + (*this).getCubeDim();
    int yBegin = (*this).getCubeY();
    int yEnd = yBegin + (*this).getCubeDim();
    int zBegin = (*this).getCubeZ();
    int zEnd = zBegin + (*this).getCubeDim();
    double voxelX;
    double voxelY;
    double voxelZ;


    for(int z = zBegin; z < zEnd; z++)
    {
        for(int y = yBegin; y < yEnd; y++)
        {
            for(int x = xBegin; x < xEnd; x++)
            {
                voxelX = x + 0.5;
                voxelY = y + 0.5;
                voxelZ = z + 0.5;
                if((*this).findPointDistanceToCenter(voxelX, voxelY, voxelZ) <= (*this).getRadius())
                {
                    sizeIncrement++;
                } 
            }
        }
    }

    this->size = sizeIncrement;
}

double SphericalPore::findPointDistanceToCenter(double _pointX, double _pointY, double _pointZ)
{
    double distanceX = _pointX - (*this).getCenterX();
    double distanceY = _pointY - (*this).getCenterY();
    double distanceZ = _pointZ - (*this).getCenterZ();

    return sqrt((distanceX * distanceX) + (distanceY * distanceY) + (distanceZ * distanceZ));
}