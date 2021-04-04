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
#include "SquarePore.h"
#include "SyntheticRock.h"
#include "SquarePoreDrawer.h"

// Methods
SquarePoreDrawer::SquarePoreDrawer(SyntheticRock &_image) : canvas(_image)
{}

/*
    This method insert synthetic pores in the image
    @_quantity is the number of square pores
    @_family is the family of the pores to be inserted
*/
void SquarePoreDrawer::insertSquarePores(uint _quantity, string _family)
{
	uint poreCount = 0;
    uint errCount = 0;
    uint errLimit = (3 * _quantity); // number of times an insertion can fail.

    while (poreCount < _quantity && errCount < errLimit)
    {
        SquarePore pore = createNewSquarePore(_family);
        if ((*this).placeNewSquarePore(pore))
        {
            this->canvas.poreList.push_back(pore);
            poreCount++;
        }
        else
        {
            errCount++;
            if (errCount == (errLimit / 2) + 1)
            {
                this->canvas.removeLastPore();
                poreCount--;
            }
        }
    }

    if ((errCount == errLimit) && (errLimit > 0))
    {
        cout << "err: could not insert enough " << _family << " pores." << endl;
        cout << "total pores inserted: " << poreCount << endl;
    }
}

/*
    This method creates a synthetic pore with a random position
    @_family is the family of the pores to be inserted
*/
SquarePore SquarePoreDrawer::createNewSquarePore(string _family)
{
	SquarePore pore(_family);
    int minvalue = 1;
    int maxvalue = pore.length + 1;
    pore.setX((*this).randomize(minvalue, this->canvas.width - maxvalue));
    pore.setY((*this).randomize(minvalue, this->canvas.height - maxvalue));
    pore.setZ(0);

    // pore.printInfo();

    return pore;
}

/*
    This method tries to insert a synthetic @_pore in the image.
    It returns 'true' if the pore is succesfully inserted, otherwise, it returns 'false' 
*/
bool SquarePoreDrawer::placeNewSquarePore(SquarePore &_pore)
{
	// check pore edges
    int x1 = _pore.x;
    int x2 = x1 + _pore.length;
    int y1 = _pore.y;
    int y2 = y1 + _pore.length;

    if ((*this).checkNeighborPixels(x1, y1) &&
        (*this).checkNeighborPixels(x2, y1) &&
        (*this).checkNeighborPixels(x1, y2) &&
        (*this).checkNeighborPixels(x2, y2))
    {
        // draw pore
        (*this).drawSquarePore(_pore);
        return true;
    }

    return false;
}

/*
    This method checks if the pixels in the neighborhood of a point are in the rock phase.
    It returns 'false' if any pixel in the neighborhood is already of the pore phase, otherwise, it returns 'true' 
*/
bool SquarePoreDrawer::checkNeighborPixels(int _x, int _y)
{
	// set surrounding points
    int radius = 2;
    int channels = this->canvas.rockImage[0].channels();
    int x1 = (_x * channels) - radius * channels;
    int x2 = (_x * channels) + radius * channels;
    int y1 = _y - radius;
    int y2 = _y + radius;

    // apply border restrictions
    (*this).applyBorderRestrictions(x1, y1);
    (*this).applyBorderRestrictions(x2, y1);
    (*this).applyBorderRestrictions(x1, y2);
    (*this).applyBorderRestrictions(x2, y2);

    // check all surrounding points
    uchar *pixel_y;
    for (uint y = y1; y < y2; y++)
    {
        pixel_y = this->canvas.rockImage[0].ptr<uchar>(y);
        for (uint x = x1; x < x2; x++)
        {
            if (pixel_y[x] != this->canvas.rock_color) // if pixel is occupied
                return false;
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
void SquarePoreDrawer::applyBorderRestrictions(int &_x, int &_y)
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
}

/*
    This method draw a synthetic @_pore in the image.
*/
void SquarePoreDrawer::drawSquarePore(SquarePore &_pore)
{
	// pore edges
    int channels = this->canvas.rockImage[0].channels();
    uint x1 = (_pore.x * channels);
    uint x2 = x1 + _pore.length * channels;
    uint y1 = _pore.y;
    uint y2 = y1 + _pore.length;

    // draw pore
    for (uint y = 0; y < _pore.length; y++)
    {
        uchar *current_pixel;
        current_pixel = this->canvas.rockImage[0].ptr<uchar>(y1 + y);
        for (uint x = 0; x < (_pore.length * channels); x++)
        {
            current_pixel[x1 + x] = this->canvas.pore_color;
        }
    }
}

/*
    This method erases a synthetic @_pore in the image.
*/
void SquarePoreDrawer::eraseSquarePore(SquarePore &_pore)
{
	// pore edges
    int channels = this->canvas.rockImage[0].channels();
    uint x1 = (_pore.x * channels);
    uint x2 = x1 + _pore.length * channels;
    uint y1 = _pore.y;
    uint y2 = y1 + _pore.length;

    // draw pore
    for (uint y = 0; y < _pore.length; y++)
    {
        uchar *current_pixel;
        current_pixel = this->canvas.rockImage[0].ptr<uchar>(y1 + y);
        for (uint x = 0; x < (_pore.length * channels); x++)
        {
            current_pixel[x1 + x] = this->canvas.rock_color;
        }
    }
}

/*
    This method erases a synthetic @_pore in the image.
*/
void SquarePoreDrawer::eraseRoughnessInPore(SquarePore &_pore)
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
void SquarePoreDrawer::removeFamilyOfPores(string _family)
{
	for (int pore = (this->canvas.poreList.size() - 1); pore >= 0; pore--)
    {
        SquarePore newPore(this->canvas.poreList[pore]);
        if (newPore.family == _family)
        {
            // erase roughness effect in pore
            (*this).eraseRoughnessInPore(newPore);

            // erase pore from image
            (*this).eraseSquarePore(newPore);

            // remove pore from list
            this->canvas.poreList.erase(this->canvas.poreList.begin() + pore);
        }
    }
}

/*
    This method applies a filter that inserts roughness in every pore "wall"
*/
void SquarePoreDrawer::applyRoughness()
{
	for (uint id = 0; id < this->canvas.poreList.size(); id++)
    {
        if(this->canvas.poreList[id].getType() == "square")
        {
            SquarePore pore = this->canvas.poreList[id];
            (*this).applyHorizontalRoughness(pore);
            (*this).applyVerticalRoughness(pore);
        }
    }
}

/*
    This method applies a filter that inserts roughness in every pore of a give @_family
*/
void SquarePoreDrawer::applyRoughness(string _family)
{
	for (uint id = 0; id < this->canvas.poreList.size(); id++)
    {
        if (this->canvas.poreList[id].getType() == "square")
        {   
            SquarePore pore = this->canvas.poreList[id];
            if (pore.family == "_family")
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
void SquarePoreDrawer::removeRoughness()
{
	this->canvas.invertColors();   

    for (uint id = 0; id < this->canvas.poreList.size(); id++)
    {
        if(this->canvas.poreList[id].getType() == "square")
        {
            SquarePore pore = this->canvas.poreList[id];
            (*this).applyHorizontalRoughness(pore);
            (*this).applyVerticalRoughness(pore);
        }
    }

    this->canvas.invertColors();
}

/*
    This method removes the roughness inserted in every pore of a given @_family
*/
void SquarePoreDrawer::removeRoughness(string _family)
{
	this->canvas.invertColors();

    for (uint id = 0; id < this->canvas.poreList.size(); id++)
    {
        if (this->canvas.poreList[id].getType() == "square")
        {   
            SquarePore pore = this->canvas.poreList[id];
            if (pore.family == "_family")
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
void SquarePoreDrawer::applyVerticalRoughness(SquarePore &_pore)
{
	// set surrounding points
    int channels = this->canvas.rockImage[0].channels();
    int shell_x1 = (_pore.x - 1) * channels;
    int shell_x2 = shell_x1 + (_pore.length + 1) * channels;
    int shell_y1 = _pore.y - 1;
    int shell_y2 = shell_y1 + (_pore.length + 1);

    // apply image border restrictions
    (*this).applyBorderRestrictions(shell_x1, shell_y1);
    (*this).applyBorderRestrictions(shell_x2, shell_y1);
    (*this).applyBorderRestrictions(shell_x1, shell_y2);
    (*this).applyBorderRestrictions(shell_x2, shell_y2);

    // create rough layer
    (*this).createVerticalRoughness(shell_x1, shell_y1, shell_y2);
    (*this).createVerticalRoughness(shell_x2, shell_y1, shell_y2);
}

/*
    This method draws the roughness effect in an vertical straight line
    @_x is the x coordinate
    @_y1 is the y initial coordinate
    @_y2 is the y final coordinate
*/
void SquarePoreDrawer::createVerticalRoughness(int _x, int _y1, int _y2)
{
    // parameters
    int channels = this->canvas.rockImage[0].channels();
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
            pixel = this->canvas.rockImage[0].ptr<uchar>(y);
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
void SquarePoreDrawer::applyHorizontalRoughness(SquarePore &_pore)
{
	// set surrounding points
    int channels = this->canvas.rockImage[0].channels();
    int shell_x1 = (_pore.x - 1) * channels;
    int shell_x2 = shell_x1 + (_pore.length + 1) * channels;
    int shell_y1 = _pore.y - 1;
    int shell_y2 = shell_y1 + (_pore.length + 1);

    // apply image border restrictions
    (*this).applyBorderRestrictions(shell_x1, shell_y1);
    (*this).applyBorderRestrictions(shell_x2, shell_y1);
    (*this).applyBorderRestrictions(shell_x1, shell_y2);
    (*this).applyBorderRestrictions(shell_x2, shell_y2);

    // create rough layer
    (*this).createHorizontalRoughness(shell_y1, shell_x1, shell_x2);
    (*this).createHorizontalRoughness(shell_y2, shell_x1, shell_x2);
}

/*
    This method draws the roughness effect in an horizontal straight line
    @_y is the y coordinate
    @_x1 is the x initial coordinate
    @_x2 is the x final coordinate
*/
void SquarePoreDrawer::createHorizontalRoughness(int _y, int _x1, int _x2)
{
    // parameters
    int channels = this->canvas.rockImage[0].channels();
    int begin;
    int end;
    uchar *pixel;

    // apply rugosity at pore faces
    begin = _x1 + channels;
    end = _x2;
    pixel = this->canvas.rockImage[0].ptr<uchar>(_y);
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

uint SquarePoreDrawer::randomize(uint _begin, uint _end)
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