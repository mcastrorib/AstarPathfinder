#ifndef CANVAS_H
#define CANVAS_H

// include C++ standard libraries
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>

// include OpenCV core functions
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

// include other PathFinder classes
#include "mGrid.h"
#include "mNode.h"


#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 800
#define GRID_LINEWIDTH 2
#define BG_COLOR {127, 127, 127}
#define GRID_COLOR {0, 0, 0}

using namespace std;

class Canvas
{
public:
	cv::Mat *image; 
    mGrid *grid;
    int nodeSizeX;
    int nodeSizeY;
    cv::Scalar backgroundColor;
    cv::Scalar gridColor;
    int gridLinewidth;
    int imageChannels;
    int imageWidth;
    int imageHeight;
    string windowName;
    
	Canvas(mGrid *_grid) : windowName("Main Window"), grid(_grid)
	{
		this->backgroundColor = BG_COLOR;
		this->gridColor = GRID_COLOR;
		this->gridLinewidth = GRID_LINEWIDTH;
		(*this).resizeImage();
		image = new cv::Mat(this->imageHeight, this->imageWidth, CV_8UC3, this->backgroundColor);
		this->imageChannels = image->channels();
		(*this).drawGridLines();
	}

	Canvas(const Canvas &_otherCanvas)
	{
		this->image = _otherCanvas.image;
		this->grid = _otherCanvas.grid;
		this->nodeSizeX = _otherCanvas.nodeSizeX;
		this->nodeSizeY = _otherCanvas.nodeSizeY;
		this->imageChannels = _otherCanvas.imageChannels;
		this->imageWidth = _otherCanvas.imageWidth;
		this->imageHeight = _otherCanvas.imageHeight;
		this->windowName = _otherCanvas.windowName;
	}

	virtual ~Canvas()
	{
		if(image != NULL)
		{
			delete image;
			image = NULL;
			// cout << "image deleted" << endl;
		}

		if(grid != NULL)
		{
			delete grid;
			grid = NULL;
			// cout << "grid deleted" << endl;
		}

		cout << "canvas deleted" << endl;
	};

	void show()
	{
		cv::imshow(this->windowName, (*image));
		cv::waitKey(0); // Wait for a keystroke in the window
	}

	void resizeImage()
	{
		int dimX = CANVAS_WIDTH / this->grid->gridDimX;
		int dimY = CANVAS_HEIGHT / this->grid->gridDimY;

		this->imageWidth = dimX * this->grid->gridDimX + (this->grid->gridDimX - 1) * this->gridLinewidth;
		this->imageHeight = dimY * this->grid->gridDimY + (this->grid->gridDimY - 1) * this->gridLinewidth;

		this->nodeSizeX = dimX;
		this->nodeSizeY = dimY;
	}

	void drawGridLines()
	{
		int rows = this->grid->gridDimY;
		int cols = this->grid->gridDimX;
		int verticalLines = cols - 1;
		int horizontalLines = rows - 1;

		int posX = this->nodeSizeX;
		for(int vline = 0; vline < verticalLines; vline++)
		{
			(*this).drawVerticalLine(posX, this->gridColor, this->gridLinewidth);
			posX += this->nodeSizeX + this->gridLinewidth;
		}

		int posY = this->nodeSizeY;
		for(int hline = 0; hline < horizontalLines; hline++)
		{
			(*this).drawHorizontalLine(posY, this->gridColor, this->gridLinewidth);
			posY += this->nodeSizeY + this->gridLinewidth;
		}
	}
	
	void drawVerticalLine(int _x, cv::Scalar _color, int _linewidth)
	{
		int x0 = _x * this->imageChannels;
		int xf = x0 + _linewidth * this->imageChannels;
		
		for(int x = x0; x < xf; x += this->imageChannels)
		{
			if(x > 0 and 
			   x < this->imageWidth * this->imageChannels and 
			   x + (this->imageChannels - 1) < this->imageWidth * this->imageChannels)
			{
				for (uint y = 0; y < this->imageHeight; y++)
			    {
			        uchar *current_pixel;
			        current_pixel = image->ptr<uchar>(y);
			        current_pixel[x + 0] = _color[0];
			        current_pixel[x + 1] = _color[1];
			        current_pixel[x + 2] = _color[2];
			    }
			}
		}
	}

	void drawHorizontalLine(int _y, cv::Scalar _color, int _linewidth)
	{
		int y0 = _y;
		int yf = y0 + _linewidth;
		
		for(int y = y0; y < yf; y++)
		{
			if(y > 0 and y < this->imageHeight) 
			   {
				for (uint x = 0; x < this->imageWidth * this->imageChannels; x += this->imageChannels)
			    {
			        uchar *current_pixel;
			        current_pixel = image->ptr<uchar>(y);
			        current_pixel[x + 0] = _color[0];
			        current_pixel[x + 1] = _color[1];
			        current_pixel[x + 2] = _color[2];
			    }
			}
		}
	}

	void drawRectangle(int _x, int _y, cv::Scalar _color, int _lx, int _ly)
	{
		int x0 = _x * this->imageChannels;
		int xf = (_x + _lx) * this->imageChannels;
		int y0 = _y ;
		int yf = _y + _ly;

		if(x0 < 0 or xf > this->imageWidth*this->imageChannels or y0 < 0 or yf > this->imageHeight)
		{
			cout << "coords are beyond image limits" << endl;
			return;
		}
		
		for(int y = y0; y < yf; y++)
		{
			for (uint x = x0; x < xf; x += this->imageChannels)
		    {
		        // cout << "got here 4" << endl;
			    uchar *current_pixel;
		        current_pixel = image->ptr<uchar>(y);
		        current_pixel[x + 0] = _color[0];
		        current_pixel[x + 1] = _color[1];
		        current_pixel[x + 2] = _color[2];
		    }
		}
	}
};


#endif