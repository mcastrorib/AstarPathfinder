// include C++ standard libraries
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include <vector>
#include <string>

// include OpenCV core functions
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

// include header file
#include "Pore.h"
#include "SphericalPore.h"
#include "SyntheticRock.h"
#include "SphericalPoreDrawer.h"

// Methods
SphericalPoreDrawer::SphericalPoreDrawer(SyntheticRock &_image) : canvas(_image)
{}

void SphericalPoreDrawer::insertSphericalLatticeArray(int _latticeEdge, double _sphereRadius, bool _overlap)
{
    double latticeCenter = ((double) _latticeEdge) * 0.5;
    int channels = this->canvas.rockImage[0].channels();
    int rows = (int) ceil(this->canvas.width / (double) _latticeEdge);
    int columns = (int) ceil(this->canvas.height / (double) _latticeEdge);
    int slices = (int) ceil(this->canvas.depth / (double) _latticeEdge);

    for(int slice = 0; slice < slices; slice++)
    {
        for(int column = 0; column < columns; column++)
        {
            for(int row = 0; row < rows; row++)
            {
                // set center o current lattice
                double centerX = latticeCenter + row * _latticeEdge;
                double centerY = latticeCenter + column * _latticeEdge;
                double centerZ = latticeCenter + slice * _latticeEdge;

                SphericalPore sphere(centerX, centerY, centerZ, _sphereRadius);
                (*this).insertSphericalPore(sphere, _overlap);
            }
        }
    }    
}

void SphericalPoreDrawer::removeSphericalLatticeArray(int _latticeEdge, double _sphereRadius, bool _overlap)
{
    this->canvas.invertColors();
    (*this).insertSphericalLatticeArray(_latticeEdge, _sphereRadius, _overlap);
    this->canvas.invertColors();
}

/*
    This method insert synthetic pores in the image
    @_quantity is the number of square pores
    @_family is the family of the pores to be inserted
*/
void SphericalPoreDrawer::insertSphericalPore(SphericalPore &_pore, bool _overlap)
{
	if ((*this).placeNewSphericalPore(_pore, _overlap))
    {
        this->canvas.poreList.push_back(_pore);
        // cout << "pore inserted with size " << pore.getSize() << endl;       
    }
}

/*
    This method tries to insert a synthetic @_pore in the image.
    It returns 'true' if the pore is succesfully inserted, otherwise, it returns 'false' 
*/
bool SphericalPoreDrawer::placeNewSphericalPore(SphericalPore &_pore, bool _overlap)
{

    if ((*this).checkPorePixels(_pore, _overlap))
    {
        // draw pore
        (*this).drawSphericalPore(_pore);
        return true;
    }

    return false;
}

/*
    This method checks if the pixels in the neighborhood of a point are in the rock phase.
    It returns 'false' if any pixel in the neighborhood is already of the pore phase, otherwise, it returns 'true' 
*/
bool SphericalPoreDrawer::checkPorePixels(SphericalPore &_pore, bool _overlap)
{
    int channels = this->canvas.rockImage[0].channels();

    // pore edges
    int x1 = _pore.getCubeX() * channels;
    int x2 = x1 + (_pore.getCubeDim()) * channels;
    int y1 = _pore.getCubeY();
    int y2 = y1 + _pore.getCubeDim();
    int z1 = _pore.getCubeZ();
    int z2 = z1 + _pore.getCubeDim();


    // apply border restrictions
    (*this).applyBorderRestrictions(x1, y1, z1);
    (*this).applyBorderRestrictions(x2, y1, z1);
    (*this).applyBorderRestrictions(x1, y2, z1);
    (*this).applyBorderRestrictions(x2, y2, z1);
    (*this).applyBorderRestrictions(x1, y1, z2);
    (*this).applyBorderRestrictions(x2, y1, z2);
    (*this).applyBorderRestrictions(x1, y2, z2);
    (*this).applyBorderRestrictions(x2, y2, z2);

    // check all surrounding points if no overlap allowed
    if(_overlap == false)
    {
        uchar *pixel_y;
        double voxelX, voxelY, voxelZ;
        double voxelOffset = 0.5;
        double convertX = 1.0 / (double) channels;
        for(uint z = z1; z < z2; z++)
        {
            for (uint y = y1; y < y2; y++)
            {
                pixel_y = this->canvas.rockImage[z].ptr<uchar>(y);
                for (uint x = x1; x < x2; x++)
                {
                    // set voxel center with 0.5 offset
                    voxelX = x * convertX + voxelOffset;
                    voxelY = y + voxelOffset;
                    voxelZ = z + voxelOffset;
    
                    if(_pore.findPointDistanceToCenter(voxelX, voxelY, voxelZ) <= _pore.getRadius())
                    {
                        if (pixel_y[x] != this->canvas.rock_color) // if pixel is occupied
                            return false;
                    }
                }
            }
        }
    }

    // point passed test
    return true;
}

/*
    This method checks if the input coord pixels are within the image.
    @_x is the x coordinate
    @_y is the y coordinate
*/
void SphericalPoreDrawer::applyBorderRestrictions(int &_x, int &_y, int &_z)
{
	// apply left border limits
    if (_x < 0)
        _x = 0;

    // apply right border limits
    if (_x >= (this->canvas.width * this->canvas.rockImage[0].channels()))
        _x = (this->canvas.width * this->canvas.rockImage[0].channels());

    // apply upper border limits
    if (_y < 0)
        _y = 0;

    // apply lower border limits
    if (_y >= this->canvas.height)
        _y = this->canvas.height;

    // apply front border limits
    if (_z < 0)
        _z = 0;

    // apply back border limits
    if (_z >= this->canvas.depth)
        _z = this->canvas.depth - 1;
}

/*
    This method draw a synthetic @_pore in the image.
*/
void SphericalPoreDrawer::drawSphericalPore(SphericalPore &_pore)
{
	int channels = this->canvas.rockImage[0].channels();

    // pore edges
    int x1 = _pore.getCubeX() * channels;
    int x2 = x1 + (_pore.getCubeDim()) * channels;
    int y1 = _pore.getCubeY();
    int y2 = y1 + _pore.getCubeDim();
    int z1 = _pore.getCubeZ();
    int z2 = z1 + _pore.getCubeDim();

    // apply border restrictions
    (*this).applyBorderRestrictions(x1, y1, z1);
    (*this).applyBorderRestrictions(x2, y1, z1);
    (*this).applyBorderRestrictions(x1, y2, z1);
    (*this).applyBorderRestrictions(x2, y2, z1);
    (*this).applyBorderRestrictions(x1, y1, z2);
    (*this).applyBorderRestrictions(x2, y1, z2);
    (*this).applyBorderRestrictions(x1, y2, z2);
    (*this).applyBorderRestrictions(x2, y2, z2);

    // check all surrounding points
    uchar *currentPixel;
    double voxelX, voxelY, voxelZ;
    double voxelOffset = 0.5;
    double convertX = 1.0 / (double) channels;
    x1 = x1 / channels;
    x2 = x2 / channels;
    for(uint z = z1; z < z2; z++)
    {
        for (uint y = y1; y < y2; y++)
        {
            currentPixel = this->canvas.rockImage[z].ptr<uchar>(y);
            for (uint x = x1; x < x2; x++)
            {
                // set voxel center with 0.5 offset
                voxelX = x + voxelOffset;
                voxelY = y + voxelOffset;
                voxelZ = z + voxelOffset;
                
                if(_pore.findPointDistanceToCenter(voxelX, voxelY, voxelZ) <= _pore.getRadius())
                {
                    for(int channel = 0; channel < channels; channel++)
                    {
                        int index = x * channels + channel;
                        currentPixel[index] = this->canvas.pore_color;
                    }
                }
            }
        }
    }
}

/*
    This method erases a synthetic @_pore in the image.
*/
void SphericalPoreDrawer::eraseSphericalPore(SphericalPore &_pore)
{
	this->canvas.invertColors();
    (*this).drawSphericalPore(_pore);
    this->canvas.invertColors();
}

uint SphericalPoreDrawer::randomUint(uint _begin, uint _end)
{
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(_begin, _end);

    // RNG warm up
    uint garbage;
    for (uint i = 0; i < 100; i++)
    {
        garbage = dist(rng);
    }

    return (dist(rng));
}

int SphericalPoreDrawer::randomInt(int _begin, int _end)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(_begin, _end);

    // RNG warm up
    uint garbage;
    for (uint i = 0; i < 100; i++)
    {
        garbage = dist(rng);
    }

    return (dist(rng));
}