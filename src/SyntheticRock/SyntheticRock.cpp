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

// include drawer files
#include "SquarePoreDrawer.h"
#include "PrismaticPoreDrawer.h"
#include "SphericalPoreDrawer.h"
#include "PlaneBarrierDrawer.h"

// include header file
#include "SyntheticRock.h"

using namespace std;
using namespace cv;

// SyntheticRock methods
// default constructor

/*
/   Default constructor with no parameters passed throughout
/   every attribute is initialized as zero (except for the porosity, as it is by default 100%)
/   the project is named 'untitled
*/
SyntheticRock::SyntheticRock() : height(0),
                                 width(0),
                                 depth(0),
                                 rock_color(GRAY),
                                 pore_color(BLACK),
                                 porosity(1.0),
                                 name("untitled")
{
    (*this).setDirectory("../images/" + this->name);
    vector<Mat> rockImage();
    vector<Pore> poreList();
}

/*
/   Default constructor initialized with param 'name'
/   every attribute is initialized as zero (except for the porosity, as it is by default 100%)
/   @_name is the project name
*/
SyntheticRock::SyntheticRock(string _name) : height(0),
                                             width(0),
                                             depth(0),
                                             rock_color(GRAY),
                                             pore_color(BLACK),
                                             porosity(1.0),
                                             name(_name)
{
    (*this).setDirectory("../images/" + this->name);
    vector<Mat> rockImage();
    vector<Pore> poreList();
}

/*
/   Default constructor initialized with params 
/   @_h is the image's height
/   @_w is the image's width
/   @_d is the image's depth 
/   @_name is the project name
/   the porosity attribute is initiallized as 100%
*/
SyntheticRock::SyntheticRock(uint _h, uint _w, uint _d, string _name) : height(_h),
                                                                        width(_w),
                                                                        depth(_d),
                                                                        rock_color(GRAY),
                                                                        pore_color(BLACK),
                                                                        porosity(1.0),
                                                                        name(_name)
{
    (*this).setDirectory("../images/" + this->name);
    vector<Mat> rockImage();
    vector<Pore> poreList();
}

// SyntheticRock copy constructor
SyntheticRock::SyntheticRock(const SyntheticRock &_otherRock)
{
    // file attributes
    this->name = _otherRock.name;
    this->directory = _otherRock.directory;

    // image attributes
    this->height = _otherRock.height;
    this->width = _otherRock.width;
    this->depth = _otherRock.depth;

    // deep copy of images // redraw all the pores from list!!!!
    this->rockImage = (*this).copyRockImage(_otherRock.rockImage);

    this->rock_color = _otherRock.rock_color;
    this->pore_color = _otherRock.pore_color;

    // pore list
    // this->poreList = (*this).copyPoreList(_otherRock.poreList);
    this->poreList = _otherRock.poreList;
    this->porosity = _otherRock.porosity;
}

/*
    This method creates a blank 2D image using openCV resources
    This image is equivalent to a 2D dense synthetic rock slice with no pores
*/
void SyntheticRock::createBlankImage()
{
    // check if image is cleared
    if (this->rockImage.size() > 0)
    {
        this->rockImage.clear();
    }

    Mat Img(this->width, this->height, CV_8UC3, Scalar(rock_color, rock_color, rock_color));
    this->rockImage.push_back(Img);

    (*this).updatePorosity();
}

/*
    This method creates blank 2D images using openCV resources
    This image is equivalent to a 3D dense synthetic rock with no pores
*/
void SyntheticRock::createBlankRock()
{

    Mat Img(this->width, this->height, CV_8UC3, Scalar(rock_color, rock_color, rock_color));

    for (uint slice = 0; slice < this->depth; slice++)
    {
        Mat deepCopy;
        Img.copyTo(deepCopy);
        this->rockImage.push_back(deepCopy);
    }
}

/*
    This method creates an image with synthetic pores 
    @_bigPores is the number of square pores of family 'big'
    @_mediumPores is the number of square pores of family 'medium'
    @_smallPores is the number of square pores of family 'small'
*/
void SyntheticRock::createPorousImage(uint _bigPores, uint _mediumPores, uint _smallPores)
{
    if (this->rockImage.size() == 0)
    {
        (*this).createBlankImage();
    }

    SquarePoreDrawer drawer(*this);
    drawer.insertSquarePores(_bigPores, "big");
    drawer.insertSquarePores(_mediumPores, "medium");
    drawer.insertSquarePores(_smallPores, "small");

    // update porosity attribute
    (*this).updatePorosity();
}

/*
    This alternative method creates an image with synthetic pores
    @_pores is the number of square pores
    @_family is the family of the pores to be inserted
*/
void SyntheticRock::createPorousImage(uint _pores, string _family)
{
    if (this->rockImage.size() == 0)
    {
        (*this).createBlankImage();
    }

    SquarePoreDrawer drawer(*this);
    drawer.insertSquarePores(_pores, _family);

    // update porosity attribute
    (*this).updatePorosity();
}

/*
    This alternative method inserts random prismatic pores in the image
    @_family is the family of the pores to be inserted
    @_porosity is the target porosity added by this insertion
*/
void SyntheticRock::insertFamilyOfPores(PrismaticPoreFamily _family, double _porosity)
{
    if (this->rockImage.size() == 0)
    {
        if(this->depth == 1)
            (*this).createBlankImage();
        else
            (*this).createBlankRock();
    }

    PrismaticPoreDrawer drawer(*this);
    drawer.insertPrismaticPores(_family, _porosity);

    // update porosity attribute
    (*this).updatePorosity();
}

/*
    This method creates a pore barrier parallel to plane xy at z = @coordZ.
*/
void SyntheticRock::insertBarrierPlaneXY(uint _coordZ)
{
    if (this->rockImage.size() == 0)
    {
        if(this->depth == 1)
            (*this).createBlankImage();
        else
            (*this).createBlankRock();
    }

    cout << "creating xy plane at coord " << _coordZ << endl;
    PlaneBarrierDrawer drawer(*this);
    drawer.insertPlaneXY(_coordZ);

    // update porosity attribute
    (*this).updatePorosity();
}

/*
    This method creates a pore barrier parallel to plane xz at y = @coordY.
*/
void SyntheticRock::insertBarrierPlaneXZ(uint _coordY)
{
    if (this->rockImage.size() == 0)
    {
        if(this->depth == 1)
            (*this).createBlankImage();
        else
            (*this).createBlankRock();
    }

    cout << "creating xz plane at coord " << _coordY << endl;
    PlaneBarrierDrawer drawer(*this);
    drawer.insertPlaneXZ(_coordY);

    // update porosity attribute
    (*this).updatePorosity();
}


/*
    This method creates a pore barrier parallel to plane yz at x = @coordX.
*/
void SyntheticRock::insertBarrierPlaneYZ(uint _coordX)
{
    if (this->rockImage.size() == 0)
    {
        if(this->depth == 1)
            (*this).createBlankImage();
        else
            (*this).createBlankRock();
    }

    cout << "creating yz plane at coord " << _coordX << endl;
    PlaneBarrierDrawer drawer(*this);
    drawer.insertPlaneYZ(_coordX);

    // update porosity attribute
    (*this).updatePorosity();
}

/*
    This method removes the last synthetic pore inserted in the image.
*/
void SyntheticRock::removeLastPore()
{
    Pore lastPore(this->poreList.back());
    
    if(lastPore.type == "square")
    {
        SquarePore lastSquarePore(lastPore); 
        SquarePoreDrawer drawer(*this);
        drawer.eraseSquarePore(lastSquarePore);
    }
    if(lastPore.type == "prismatic")
    {
        PrismaticPore lastPrismaticPore(lastPore);
        PrismaticPoreDrawer drawer(*this);
        drawer.erasePrismaticPore(lastPrismaticPore);
    }

    this->poreList.pop_back();
}


/*
    This method updates the porosity attribute of the SyntheticRock object
*/
void SyntheticRock::updatePorosity()
{
    if(this->rockImage.size() == 0) 
    {
        this->porosity = -1.0; 
        return;
    }

    double totalPixels = (double)(this->height * this->width * this->depth);
    uint porePixels = 0;

    // count pores
    int channels = this->rockImage[0].channels();
    int x_resolution = this->width * channels;
    int y_resolution = this->height;
    int z_resolution = this->depth;

    uchar *pixel;
    for(int z = 0; z < z_resolution; z++)
    {
        for (int y = 0; y < y_resolution; y++)
        {
            pixel = this->rockImage[z].ptr<uchar>(y);
            for (int x = 0; x < x_resolution; x = x + channels)
            {
                // check if pixel is pore
                if (pixel[x] != this->rock_color)
                    porePixels++;
            }
        }
    }
    this->porosity = porePixels / totalPixels;
}

/*
    This method applies a filter that removes all pores from a given family of pores
    @_family is the family to be removed
*/
void SyntheticRock::removeFamilyOfPores(string _family)
{
    SquarePoreDrawer drawer(*this);
    drawer.removeFamilyOfPores(_family);

    // update image porosity
    (*this).updatePorosity();
}

/*
    This method applies a filter that removes all pores from a given family of pores
    @_family is the family to be removed
*/
void SyntheticRock::removeFamilyOfPores(PrismaticPoreFamily _family)
{
    PrismaticPoreDrawer drawer(*this);
    drawer.removeFamilyOfPores(_family);

    // update image porosity
    (*this).updatePorosity();
}

/*
    This method applies a filter that removes all pores with size within the interval
    @_minsize and @_maxsize 
*/
void SyntheticRock::removePoresInSizeInterval(uint _maxsize, uint _minsize)
{
    PrismaticPoreDrawer drawer(*this);
    drawer.removePoresInSizeInterval(_maxsize, _minsize);

    // update image porosity
    (*this).updatePorosity();
}

/*
    This method inverts the colors of the rock and porous phases for next drawings
*/
void SyntheticRock::invertColors()
{
    uchar temp_color = this->pore_color;
    this->pore_color = this->rock_color;
    this->rock_color = temp_color;
}

/*
    This method inverts the colors of the rock and porous phases in the image already drawed
*/
void SyntheticRock::flipColorsInImage(bool _invertColors)
{
    (*this).flipEachPixelColor();
    if(_invertColors) (*this).invertColors();
    (*this).updatePorosity();
}

/*
    This method loops throughout all the pixels in image
    fliping the colors of the rock and porous phases 
*/
void SyntheticRock::flipEachPixelColor()
{
    if(this->rockImage.size() != 0)
    {    
        // count pores
        int channels = this->rockImage[0].channels();
        int x_resolution = this->width * channels;
        int y_resolution = this->height;
        int z_resolution = this->depth;
    
        uchar *pixel;
        for(int z = 0; z < z_resolution; z++)
        {
            for (int y = 0; y < y_resolution; y++)
            {
                pixel = this->rockImage[z].ptr<uchar>(y);
                for (int x = 0; x < x_resolution; x++)
                {
                    // check if pixel is pore
                    if (pixel[x] == this->rock_color)
                        pixel[x] = this->pore_color;
                    else
                        pixel[x] = this->rock_color;                    
                }
            }
        }
    }
}

/*
    This method applies a filter that inserts roughness in every pore "wall"
*/
void SyntheticRock::applyRoughness()
{
    SquarePoreDrawer squareDrawer(*this);
    squareDrawer.applyRoughness();

    PrismaticPoreDrawer prismaticDrawer(*this);
    prismaticDrawer.applyRoughness();

    (*this).updatePorosity();
}

/*
    This method applies a filter that inserts roughness in every pore of a give @_family
*/
void SyntheticRock::applyRoughness(string _family)
{
    SquarePoreDrawer drawer(*this);
    drawer.applyRoughness(_family);

    (*this).updatePorosity();
}

/*
    This method applies a filter that inserts roughness in every pore of a give @_family
*/
void SyntheticRock::applyRoughness(PrismaticPoreFamily _family)
{
    PrismaticPoreDrawer drawer(*this);
    drawer.applyRoughness(_family);

    (*this).updatePorosity();
}

/*
    This method removes the roughness inserted in every pore "wall"
*/
void SyntheticRock::removeRoughness()
{
    SquarePoreDrawer squareDrawer(*this);
    squareDrawer.removeRoughness();

    PrismaticPoreDrawer prismaticDrawer(*this);
    prismaticDrawer.removeRoughness();
    
    (*this).updatePorosity();
}

/*
    This method removes the roughness inserted in every pore of a given @_family
*/
void SyntheticRock::removeRoughness(string _family)
{
    SquarePoreDrawer drawer(*this);
    drawer.removeRoughness(_family);

    (*this).updatePorosity();
}

/*
    This method removes the roughness inserted in every pore of a given @_family
*/
void SyntheticRock::removeRoughness(PrismaticPoreFamily _family)
{
    PrismaticPoreDrawer drawer(*this);
    drawer.removeRoughness(_family);

    (*this).updatePorosity();
}

void SyntheticRock::insertSphericalLatticeArray(int _latticeEdge, double _sphereRadius, bool _overlap)
{
    SphericalPoreDrawer drawer(*this);   
    drawer.insertSphericalLatticeArray(_latticeEdge, _sphereRadius, _overlap);

    (*this).updatePorosity();
}

void SyntheticRock::removeSphericalLatticeArray(int _latticeEdge, double _sphereRadius, bool _overlap)
{
    SphericalPoreDrawer drawer(*this);   
    drawer.removeSphericalLatticeArray(_latticeEdge, _sphereRadius, _overlap);

    (*this).updatePorosity();
}

// Image management

/*
    This method expand the 2D image in the z-direction.
*/
void SyntheticRock::expandImage(uint _begin)
{
    if (_begin == 0 || this->rockImage.size() < _begin)
    {
        cout << "** image could not be expanded." << endl;
        return;
    }

    this->rockImage.resize(_begin);
    Mat imageCopy = this->rockImage[_begin - 1].clone();

    for (uint slice = _begin; slice < this->depth; slice++)
    {
        this->rockImage.push_back(imageCopy);
    }
}

/*
    This method shows the synthetic rock image on the screen using openCV resources.
*/
void SyntheticRock::showImage(int _slice)
{
    namedWindow("Display window", WINDOW_AUTOSIZE); //Create a window for display
    imshow("Display window", this->rockImage[_slice]);
    waitKey(0); // Wait for a keystroke in the window
}

/*
    This method saves all files from project in a directory with the project's name.
*/
void SyntheticRock::save()
{
    (*this).updatePorosity();
    (*this).saveInfo();
    (*this).savePoreList();
    (*this).saveImage();
}

/*
    This method saves info regarding the synthetic image in a .txt file named 'info.txt'
*/
void SyntheticRock::saveInfo()
{
    string filename = (*this).getDirectory() + "/info.txt";

    ofstream fileObject;
    fileObject.open(filename, ios::out);
    if (fileObject.fail())
    {
        cout << "Could not open file from disc." << endl;
        return;
    }

    fileObject << "Synthetic Rock Image: " << (*this).getName() << endl;
    fileObject << "- height: \t" << std::to_string((*this).getHeight()) << endl;
    fileObject << "- width: \t" << std::to_string((*this).getWidth()) << endl;
    fileObject << "- depth: \t" << std::to_string((*this).getDepth()) << endl;
    fileObject << "- volume: \t" << std::to_string((*this).getWidth() * (*this).getHeight() * (*this).getDepth()) << endl;
    fileObject << "- pores: \t" << std::to_string(this->poreList.size()) << endl;
    fileObject << "- porosity: \t" << std::to_string((*this).getPorosity()) << endl;

    // close file
    fileObject.close();
}

/*
    This method saves a list with information of the pores drawn in a .txt file named 'pores.txt'
*/
void SyntheticRock::savePoreList()
{
    string filename = (*this).getDirectory() + "/pores.txt";

    ofstream fileObject;
    fileObject.open(filename, ios::out);
    if (fileObject.fail())
    {
        cout << "Could not open file from disc." << endl;
        return;
    }

    fileObject << "poreID, ";
    fileObject << "Type, ";
    fileObject << "posX, ";
    fileObject << "posY, ";
    fileObject << "posZ, ";
    fileObject << "dimX, ";
    fileObject << "dimY, ";
    fileObject << "dimZ, ";
    fileObject << "Size";
    fileObject << endl;

    for (uint index = 0; index < this->poreList.size(); index++)
    {
        fileObject << index << ", ";
        fileObject << this->poreList[index].getType() << ", ";
        fileObject << this->poreList[index].getX() << ", ";
        fileObject << this->poreList[index].getY() << ", ";
        fileObject << this->poreList[index].getZ() << ", ";
        fileObject << this->poreList[index].getDimX() << ", ";
        fileObject << this->poreList[index].getDimY() << ", ";
        fileObject << this->poreList[index].getDimZ() << ", ";
        fileObject << this->poreList[index].getSize() << endl;
    }

    // close file
    fileObject.close();
}

/*
    This method saves the synthetic 3D image in directory "/img" inside the main project's directory
*/
void SyntheticRock::saveImage()
{
    // creates a directory with project name
    string path = this->directory + "/imgs";
    (*this).createDirectory(path);

    // find the number of decimal places necessary to identify all images
    int decimals = (*this).findDecimals(this->rockImage.size());

    for (uint slice = 0; slice < this->rockImage.size(); slice++)
    {
        (*this).saveImageSlice(path, slice, decimals);
    }
}

/*
    This method saves each 2D synthetic image slice
*/
void SyntheticRock::saveImageSlice(string _path, int _slice, int _decimals)
{
    // assemble image file name
    string fullpath = _path + "/";
    string fileID = (*this).convertFileIDToString(_slice, _decimals);
    string extension = ".png";
    string filename = fullpath + this->name + "_" + fileID + extension;

    // save image file
    imwrite(filename, this->rockImage[_slice]);
}

/*
    This method returns a deep copy of an input Image @_image
*/
vector<Mat> SyntheticRock::copyRockImage(const vector<Mat> &_image)
{
    vector<Mat> copies;
    for (uint i = 0; i < _image.size(); i++)
    {
        Mat imageCopy;
        _image[i].copyTo(imageCopy);
        copies.push_back(imageCopy);
    }

    return copies;
}

/*
    This method returns a deep copy of a vector containing a pore list @_porelist
*/
vector<Pore> SyntheticRock::copyPoreList(const vector<Pore> &_poreList)
{
    vector<Pore> copies;
    for(uint i = 0; i < _poreList.size(); i++)
    {
        Pore newPore;
        newPore.setX(_poreList[i].getX());
        newPore.setY(_poreList[i].getY());
        newPore.setZ(_poreList[i].getZ());
        newPore.setDimX(_poreList[i].getDimX());
        newPore.setDimY(_poreList[i].getDimY());
        newPore.setDimZ(_poreList[i].getDimZ());
        newPore.setType(_poreList[i].getType());
        newPore.setSize();
        copies.push_back(newPore);
    }

    return copies;
}


// Private methods
/*
    This method generates a random integer number in the interval 
    [@_begin, @_end]
*/
uint SyntheticRock::randomize(uint _begin, uint _end)
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

/*
    This method creates a directory in the user's file system
    @_fullpath is the path to the directory
*/
void SyntheticRock::createDirectory(string _fullpath)
{

    char directory[_fullpath.size() + 1];
    strcpy(directory, _fullpath.c_str());

    struct stat st = {0};

    if (stat(directory, &st) == -1)
    {
        mkdir(directory, 0700);
    }
}

/*
    This method converts a integer @_n to an output format as exampled:
    @_n = 67
    @_decimals = 3
    return = 067
*/
string SyntheticRock::convertFileIDToString(uint _n, uint _decimals)
{
    stringstream result;
    result << std::setfill('0') << std::setw(_decimals) << _n;
    return result.str();
}

/*
    This method finds the number of decimals necessary to format @_n entities
    Example:
    @_n = 1,    return = 1
    @_n = 923,  return = 3
    @_n = 25,   return = 2
    
*/
int SyntheticRock::findDecimals(int _n)
{
    int count = 1;
    int result = _n / 10;

    while (result > 0)
    {
        count++;
        result = result / 10;
    }

    return count;
}