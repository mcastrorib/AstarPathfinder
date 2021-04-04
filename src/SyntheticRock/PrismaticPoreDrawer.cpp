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
#include "PrismaticPore.h"
#include "SyntheticRock.h"
#include "PrismaticPoreDrawer.h"

// Methods
PrismaticPoreDrawer::PrismaticPoreDrawer(SyntheticRock &_image) : canvas(_image)
{}

/*
    This method insert synthetic pores in the image
    @_quantity is the number of square pores
    @_family is the family of the pores to be inserted
*/
void PrismaticPoreDrawer::insertPrismaticPores(PrismaticPoreFamily _family, double _porosity)
{
	double initialPorosity = this->canvas.getPorosity();
    double currentPorosity = initialPorosity;
    double targetPorosity = initialPorosity + _porosity;
    double imageVolume = (double) this->canvas.height * this->canvas.width * this->canvas.depth;
    double porosityFactor = 1.0 / imageVolume; 
    cout << "image volume is " << imageVolume << endl;
    
    uint poreCount = 0;
    uint errCount = 0;
    uint errLimit = 512; // number of times an insertion can fail consecutively.

    while ((currentPorosity < targetPorosity) && (errCount < errLimit))
    {
        PrismaticPore pore = createNewPrismaticPore(_family);
        if ((*this).placeNewPrismaticPore(pore))
        {
            this->canvas.poreList.push_back(pore);
            // cout << "pore inserted with size " << pore.getSize() << endl;

            currentPorosity += (pore.getSize() * porosityFactor);            
            // cout << "current porosity is " << currentPorosity << endl;

            poreCount++;
            errCount = 0;
        }
        else
        {
            errCount++;
            // if (errCount == (errLimit / 2) + 1)
            // {
            //     // this->canvas.removeLastPore();
            //     // this->canvas.updatePorosity();
            //     // poreCount--;
            // }
        }
    }

    if ((errCount == errLimit) && (errLimit > 0))
    {
        cout << "err: could not insert enough pores." << endl;        
    }
    cout << "total pores inserted: " << poreCount << endl;
}

/*
    This method creates a synthetic pore with a random position
    @_family is the family of the pores to be inserted
*/
PrismaticPore PrismaticPoreDrawer::createNewPrismaticPore(PrismaticPoreFamily _family)
{
    // initialize a 'empty' pore
    PrismaticPore pore(0,0,0,0,0,0);

    // set pore dimensions
    pore.setDimX((*this).randomUint(_family.minDimX, _family.maxDimX));
    pore.setDimY((*this).randomUint(_family.minDimY, _family.maxDimY));
    pore.setDimZ((*this).randomUint(_family.minDimZ, _family.maxDimZ));
    pore.setSize();

    // set pore position
    int minvalue = 1;
    int max_x = pore.getDimX() + 1;
    int max_y = pore.getDimY() + 1;
    int max_z = pore.getDimZ();
    pore.setX((*this).randomUint(minvalue, this->canvas.width - max_x));
    pore.setY((*this).randomUint(minvalue, this->canvas.height - max_y));
    pore.setZ((*this).randomUint(0, this->canvas.depth - max_z));

    // pore.printInfo();

    return pore;
}

/*
    This method tries to insert a synthetic @_pore in the image.
    It returns 'true' if the pore is succesfully inserted, otherwise, it returns 'false' 
*/
bool PrismaticPoreDrawer::placeNewPrismaticPore(PrismaticPore &_pore)
{

    if ((*this).checkPorePixels(_pore))
    {
        // draw pore
        (*this).drawPrismaticPore(_pore);
        return true;
    }

    return false;
}

/*
    This method checks if the pixels in the neighborhood of a point are in the rock phase.
    It returns 'false' if any pixel in the neighborhood is already of the pore phase, otherwise, it returns 'true' 
*/
bool PrismaticPoreDrawer::checkPorePixels(PrismaticPore &_pore)
{
    // set surrounding points
    int radius = 2;
    int channels = this->canvas.rockImage[0].channels();

    // pore edges
    int x1 = (_pore.x - radius) * channels;
    int x2 = x1 + (_pore.dim_x + 2*radius) * channels;
    int y1 = _pore.y - radius;
    int y2 = y1 + _pore.dim_y + 2*radius;
    int z1 = _pore.z - radius;
    int z2 = z1 + _pore.dim_z + 2*radius;


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
    uchar *pixel_y;
    for(uint z = z1; z < z2; z++)
    {
        for (uint y = y1; y < y2; y++)
        {
            pixel_y = this->canvas.rockImage[z].ptr<uchar>(y);
            for (uint x = x1; x < x2; x++)
            {
                if (pixel_y[x] != this->canvas.rock_color) // if pixel is occupied
                    return false;
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
void PrismaticPoreDrawer::applyBorderRestrictions(int &_x, int &_y, int &_z)
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
void PrismaticPoreDrawer::drawPrismaticPore(PrismaticPore &_pore)
{
	// pore edges
    int channels = this->canvas.rockImage[0].channels();
    uint x1 = (_pore.x * channels);
    uint x2 = x1 + _pore.dim_x * channels;
    uint y1 = _pore.y;
    uint y2 = y1 + _pore.dim_y;
    uint z1 = _pore.z;
    uint z2 = z1 + _pore.dim_z;

    // draw pore
    for(uint z = z1; z < z2; z++)
    {
        for (uint y = 0; y < _pore.dim_y; y++)
        {
            uchar *current_pixel;
            current_pixel = this->canvas.rockImage[z].ptr<uchar>(y1 + y);
            for (uint x = 0; x < (_pore.dim_x * channels); x++)
            {
                current_pixel[x1 + x] = this->canvas.pore_color;
            }
        }
    }
}

/*
    This method erases a synthetic @_pore in the image.
*/
void PrismaticPoreDrawer::erasePrismaticPore(PrismaticPore &_pore)
{
	// pore edges
    int channels = this->canvas.rockImage[0].channels();
    uint x1 = (_pore.x * channels);
    uint x2 = x1 + _pore.dim_x * channels;
    uint y1 = _pore.y;
    uint y2 = y1 + _pore.dim_y;
    uint z1 = _pore.z;
    uint z2 = z1 + _pore.dim_z;

    // erase pore
    for(uint z = z1; z < z2; z++)
    {
        for (uint y = 0; y < _pore.dim_y; y++)
        {
            uchar *current_pixel;
            current_pixel = this->canvas.rockImage[z].ptr<uchar>(y1 + y);
            for (uint x = 0; x < (_pore.dim_x * channels); x++)
            {
                current_pixel[x1 + x] = this->canvas.rock_color;
            }
        }
    }
}

/*
    This method erases a synthetic @_pore in the image.
*/
void PrismaticPoreDrawer::eraseRoughnessInPore(PrismaticPore &_pore)
{
    this->canvas.invertColors();
    (*this).applyHorizontalRoughness(_pore);
    (*this).applyVerticalRoughness(_pore);
    this->canvas.invertColors();
}

/*
    This method applies a filter that removes all pores from a given family of pores
    @_family is the family to be removed
*/
void PrismaticPoreDrawer::removeFamilyOfPores(PrismaticPoreFamily _family)
{
	for (int pore = (this->canvas.poreList.size() - 1); pore >= 0; pore--)
    {
        if(this->canvas.poreList[pore].getType() == "prismatic")
        {
            PrismaticPore newPore(this->canvas.poreList[pore]);
            // newPore.printInfo();
            if (newPore.dim_x <= _family.maxDimX && newPore.dim_x >= _family.minDimX &&
                newPore.dim_y <= _family.maxDimY && newPore.dim_y >= _family.minDimY &&
                newPore.dim_z <= _family.maxDimZ && newPore.dim_z >= _family.minDimZ)
            {
                // erase roughness effect in pore
                (*this).eraseRoughnessInPore(newPore);

                // erase pore from image
                (*this).erasePrismaticPore(newPore);

                // remove pore from list
                this->canvas.poreList.erase(this->canvas.poreList.begin() + pore);
            }
        }
    }
}

/*
    This method applies a filter that removes all pores with size within the interval
    @_minsize and @_maxsize 
*/
void PrismaticPoreDrawer::removePoresInSizeInterval(uint _maxsize, uint _minsize)
{
   for (int pore = (this->canvas.poreList.size() - 1); pore >= 0; pore--)
    {
        if(this->canvas.poreList[pore].getType() == "prismatic")
        {
            PrismaticPore newPore(this->canvas.poreList[pore]);
            // newPore.printInfo();
            if (newPore.getSize() >= _minsize && newPore.getSize() <= _maxsize)
            {
                // erase roughness effect in pore
                (*this).eraseRoughnessInPore(newPore);
    
                // erase pore from image
                (*this).erasePrismaticPore(newPore);
    
                // remove pore from list
                this->canvas.poreList.erase(this->canvas.poreList.begin() + pore);
            }
        }
    } 
}

/*
    This method applies a filter that inserts roughness in every pore "wall"
*/
void PrismaticPoreDrawer::applyRoughness()
{
	for (uint id = 0; id < this->canvas.poreList.size(); id++)
    {
        if(this->canvas.poreList[id].getType() == "prismatic")
        {
            PrismaticPore pore = this->canvas.poreList[id];
            (*this).applyHorizontalRoughness(pore);
            (*this).applyVerticalRoughness(pore);
        }
    }
}

/*
    This method applies a filter that inserts roughness in every pore of a give @_family
*/
void PrismaticPoreDrawer::applyRoughness(PrismaticPoreFamily _family)
{
	for (uint id = 0; id < this->canvas.poreList.size(); id++)
    {
        if (this->canvas.poreList[id].getType() == "prismatic")
        {
            PrismaticPore pore = this->canvas.poreList[id];
            if (pore.dim_x <= _family.maxDimX && pore.dim_x >= _family.minDimX &&
                pore.dim_y <= _family.maxDimY && pore.dim_y >= _family.minDimY &&
                pore.dim_z <= _family.maxDimZ && pore.dim_z >= _family.minDimZ)
            {
                (*this).applyHorizontalRoughness(pore);
                (*this).applyVerticalRoughness(pore);
            }
        }
    }
}

/*
    This method removes the roughness inserted in every pore "wall"
*/
void PrismaticPoreDrawer::removeRoughness()
{
	this->canvas.invertColors();

    for (uint id = 0; id < this->canvas.poreList.size(); id++)
    {
        if(this->canvas.poreList[id].getType() == "prismatic")
        {
            PrismaticPore pore = this->canvas.poreList[id];
            (*this).applyHorizontalRoughness(pore);
            (*this).applyVerticalRoughness(pore);
        }
    }

    this->canvas.invertColors();
}

/*
    This method removes the roughness inserted in every pore of a given @_family
*/
void PrismaticPoreDrawer::removeRoughness(PrismaticPoreFamily _family)
{
	this->canvas.invertColors();

    for (uint id = 0; id < this->canvas.poreList.size(); id++)
    {
        if (this->canvas.poreList[id].getType() == "prismatic")
        {
            PrismaticPore pore = this->canvas.poreList[id];
            if (pore.dim_x <= _family.maxDimX && pore.dim_x >= _family.minDimX &&
                pore.dim_y <= _family.maxDimY && pore.dim_y >= _family.minDimY &&
                pore.dim_z <= _family.maxDimZ && pore.dim_z >= _family.minDimZ)
            {
                (*this).applyHorizontalRoughness(pore);
                (*this).applyVerticalRoughness(pore);
            }
        }
    }

    this->canvas.invertColors();
}

/*
    This method applies a filter that inserts roughness 
    in the vertical faces of a @_pore
*/
void PrismaticPoreDrawer::applyVerticalRoughness(PrismaticPore &_pore)
{
	// set surrounding points
    int channels = this->canvas.rockImage[0].channels();
    int shell_x1 = (_pore.x - 1) * channels;
    int shell_x2 = shell_x1 + (_pore.dim_x + 1) * channels;
    int shell_y1 = _pore.y - 1;
    int shell_y2 = shell_y1 + (_pore.dim_y + 1);
    int shell_z1 = _pore.z;
    int shell_z2 = shell_z1 + _pore.dim_z;

    // apply image border restrictions
    (*this).applyBorderRestrictions(shell_x1, shell_y1, shell_z1);
    (*this).applyBorderRestrictions(shell_x2, shell_y1, shell_z1);
    (*this).applyBorderRestrictions(shell_x1, shell_y2, shell_z1);
    (*this).applyBorderRestrictions(shell_x2, shell_y2, shell_z1);
    (*this).applyBorderRestrictions(shell_x1, shell_y1, shell_z2);
    (*this).applyBorderRestrictions(shell_x2, shell_y1, shell_z2);
    (*this).applyBorderRestrictions(shell_x1, shell_y2, shell_z2);
    (*this).applyBorderRestrictions(shell_x2, shell_y2, shell_z2);

    // create rough layer
    for(int z = shell_z1; z < shell_z2; z++)
    {
        (*this).createVerticalRoughness(shell_x1, shell_y1, shell_y2, z);
        (*this).createVerticalRoughness(shell_x2, shell_y1, shell_y2, z);
    }
}

/*
    This method draws the roughness effect in an vertical straight line
    @_x is the x coordinate
    @_y1 is the y initial coordinate
    @_y2 is the y final coordinate
*/
void PrismaticPoreDrawer::createVerticalRoughness(int _x, int _y1, int _y2, int _z)
{
    // parameters
    int channels = this->canvas.rockImage[_z].channels();
    int begin;
    int end;
    uchar *pixel;

    // apply rugosity at pore faces
    begin = _y1 + 1;
    end = _y2;
    for (int y = begin; y < end; y++)
    {
        if ((y % 2) == (_x % 2))
        {
            pixel = this->canvas.rockImage[_z].ptr<uchar>(y);
            for (int dx = 0; dx < channels; dx++)
            {
                pixel[_x + dx] = this->canvas.pore_color;
            }
        }
    }
}

/*
    This method applies a filter that inserts roughness 
    in the horizontal faces of a @_pore
*/
void PrismaticPoreDrawer::applyHorizontalRoughness(PrismaticPore &_pore)
{
	// set surrounding points
    int channels = this->canvas.rockImage[0].channels();
    int shell_x1 = (_pore.x - 1) * channels;
    int shell_x2 = shell_x1 + (_pore.dim_x + 1) * channels;
    int shell_y1 = _pore.y - 1;
    int shell_y2 = shell_y1 + (_pore.dim_y + 1);
    int shell_z1 = _pore.z;
    int shell_z2 = shell_z1 + _pore.dim_z;

    // apply image border restrictions
    (*this).applyBorderRestrictions(shell_x1, shell_y1, shell_z1);
    (*this).applyBorderRestrictions(shell_x2, shell_y1, shell_z1);
    (*this).applyBorderRestrictions(shell_x1, shell_y2, shell_z1);
    (*this).applyBorderRestrictions(shell_x2, shell_y2, shell_z1);
    (*this).applyBorderRestrictions(shell_x1, shell_y1, shell_z2);
    (*this).applyBorderRestrictions(shell_x2, shell_y1, shell_z2);
    (*this).applyBorderRestrictions(shell_x1, shell_y2, shell_z2);
    (*this).applyBorderRestrictions(shell_x2, shell_y2, shell_z2);

    // create rough layer
    for(int z = shell_z1; z < shell_z2; z++)
    {
        (*this).createHorizontalRoughness(shell_y1, shell_x1, shell_x2, z);
        (*this).createHorizontalRoughness(shell_y2, shell_x1, shell_x2, z);
    }
}

/*
    This method draws the roughness effect in an horizontal straight line
    @_y is the y coordinate
    @_x1 is the x initial coordinate
    @_x2 is the x final coordinate
*/
void PrismaticPoreDrawer::createHorizontalRoughness(int _y, int _x1, int _x2, int _z)
{
    // parameters
    int channels = this->canvas.rockImage[_z].channels();
    int begin;
    int end;
    uchar *pixel;

    // apply rugosity at pore faces
    begin = _x1 + channels;
    end = _x2;
    pixel = this->canvas.rockImage[_z].ptr<uchar>(_y);
    for (int x = begin; x < end; x += channels)
    {
        if ((x % 2) == (_y % 2))
        {
            for (int dx = 0; dx < channels; dx++)
            {
                pixel[x + dx] = this->canvas.pore_color;
            }
        }
    }
}

uint PrismaticPoreDrawer::randomUint(uint _begin, uint _end)
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

int PrismaticPoreDrawer::randomInt(int _begin, int _end)
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