#ifndef SYNTHROCK_H_
#define SYNTHROCK_H_

// include C libraries for filesystem access
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// include C++ standard libraries
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <random>
#include <vector>
#include <string>
#include <stdint.h>

// include OpenCV core functions
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

// include pore object class
#include "Pore.h"
#include "SquarePore.h"
#include "PrismaticPore.h"
#include "SphericalPore.h"

#ifndef IMG_COLORS
#define BLACK 0
#define GRAY 127
#endif

using namespace std;
using namespace cv;

class SyntheticRock
{
public:
    // attributes
    // file attributes
    string name;
    string directory;

    // image attributes
    uint height;
    uint width;
    uint depth;
    vector<Mat> rockImage;
    uchar rock_color;
    uchar pore_color;

    // pore attributes
    double porosity;
    vector<Pore> poreList;

    // methods:
    // default constructors
    SyntheticRock();
    SyntheticRock(string _name);
    SyntheticRock(uint _h, uint _w, uint _d, string _name = "untitled");

    //copy constructors
    SyntheticRock(const SyntheticRock &_otherRock);

    // default destructor
    virtual ~SyntheticRock()
    {
        if (this->rockImage.size() > 0)
            this->rockImage.clear();
        if (this->poreList.size() > 0)
            this->poreList.clear();

        cout << "SyntheticRock object destroyed succesfully" << endl;
    }

    void createBlankImage();

    void createBlankRock();

    void createPorousImage(uint _bigPores = 0, uint _mediumPores = 0, uint _smallPores = 0);

    void createPorousImage(uint _bigPores, string family);

    void insertFamilyOfPores(PrismaticPoreFamily _family, double _porosity);

    void insertBarrierPlaneXY(uint coordZ);

    void insertBarrierPlaneXZ(uint coordY);
    
    void insertBarrierPlaneYZ(uint coordX);
    
    void removeLastPore();    

    void updatePorosity();

    void removeFamilyOfPores(string _family);

    void removeFamilyOfPores(PrismaticPoreFamily _family);

    void removePoresInSizeInterval(uint _maxsize, uint _minsize = 0);

    void invertColors();

    void flipColorsInImage(bool _invertColors = false);

    void flipEachPixelColor();

    void applyRoughness();

    void applyRoughness(string _family);

    void applyRoughness(PrismaticPoreFamily _family);

    void removeRoughness();

    void removeRoughness(string _family);

    void removeRoughness(PrismaticPoreFamily _family);

    void insertSphericalLatticeArray(int _latticeEdge, double _sphereRadius, bool _overlap);

    void removeSphericalLatticeArray(int _latticeEdge, double _sphereRadius, bool _overlap);

    // image management
    void showImage(int _slice = 0);

    void save();

    void saveInfo();

    void savePoreList();

    void saveImage();

    vector<Mat> copyRockImage(const vector<Mat> &_image);

    vector<Pore> copyPoreList(const vector<Pore> &_poreList);

    void saveImageSlice(string _path, int _slice, int _decimals);

    void expandImage(uint _begin = 1);

    // set methods
    inline void setName(string _name)
    {
        this->name = _name;
        (*this).setDirectory("../images/" + (*this).getName());
    }

    inline void setDirectory(string _path)
    {
        this->directory = _path;
        (*this).createDirectory(this->directory);
    }

    inline void setHeight(uint _height)
    {
        this->height = _height;
    }

    inline void setWidth(uint _width)
    {
        this->width = _width;
    }

    inline void setDepth(uint _depth)
    {
        this->depth = _depth;
    }

    inline void setRockColor(uchar _color)
    {
        this->rock_color = _color;
    }

    inline void setPoreColor(uchar _color)
    {
        this->pore_color = _color;
    }

    // get methods
    inline string getName() { return this->name; }
    inline string getDirectory() { return this->directory; }
    inline uint getHeight() { return this->height; }
    inline uint getWidth() { return this->width; }
    inline uint getDepth() { return this->depth; }
    inline uint getFrontWidthIndex() { return 0; }
    inline uint getFrontHeightIndex() { return 0; }
    inline uint getFrontDepthIndex() { return 0; }
    inline uint getBackWidthIndex() 
    { 
        if(this->width > 0) return ((*this).getWidth() - 1);
        else return 0;
    }
    inline uint getBackHeightIndex() 
    { 
        if(this->depth > 0) return ((*this).getHeight() - 1);
        else return 0;
    }
    inline uint getBackDepthIndex() 
    { 
        if(this->depth > 0) return ((*this).getDepth() - 1);
        else return 0;
    }

    inline vector<Mat> getRockImage() { return this->rockImage; }
    inline Mat getRockImage(uint _index) { return this->rockImage[_index]; }
    inline uchar getRockColor() { return this->rock_color; }
    inline uchar getPoreColor() { return this->pore_color; }
    inline double getPorosity() { return this->porosity; }
    inline vector<Pore> getPoreList() { return this->poreList; }
    inline Pore getPoreList(uint _index) { return this->poreList[_index]; }

    // Private methods
private:
    uint randomize(uint begin, uint end);
    void createDirectory(string fullpath);
    string convertFileIDToString(uint _n, uint _decimals);
    int findDecimals(int _n);
};

#endif