#include <string>

// include OpenCV core functions
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

// include header file
#include "Pore.h"
#include "SyntheticRock.h"
#include "PlaneBarrierDrawer.h"

// Methods
PlaneBarrierDrawer::PlaneBarrierDrawer(SyntheticRock &_image) : canvas(_image)
{}

void PlaneBarrierDrawer::insertPlaneXY(uint _coordZ)
{
	if(_coordZ >= 0 && _coordZ < this->canvas.getDepth())
	{
		// set local variables
		int channels = this->canvas.rockImage[0].channels();
		uint x0 = 0;
		uint xF = this->canvas.getWidth() * channels;
		uint y0 = 0;
		uint yF = this->canvas.getHeight();
		uchar barrierColor = this->canvas.getRockColor();

		// draw pore
	    for (uint y = y0; y < yF; y++)
	    {
	        uchar *current_pixel;
	        current_pixel = this->canvas.rockImage[_coordZ].ptr<uchar>(y);
	        for (uint x = x0; x < xF; x++)
	        {
	            current_pixel[x] = barrierColor;
	        }
	    }

	} else
	{
		cout << "coord z is out of image depth." << endl;
		return;
	}
}

void PlaneBarrierDrawer::insertPlaneXZ(uint _coordY)
{
	if(_coordY >= 0 && _coordY < this->canvas.getHeight())
	{
		// set local variables
		int channels = this->canvas.rockImage[0].channels();
		uint x0 = 0;
		uint xF = this->canvas.getWidth() * channels;
		uint z0 = 0;
		uint zF = this->canvas.getDepth();
		uchar barrierColor = this->canvas.getRockColor();

		// draw pore
	    for (uint z = z0; z < zF; z++)
	    {
	        uchar *current_pixel;
	        current_pixel = this->canvas.rockImage[z].ptr<uchar>(_coordY);
	        for (uint x = x0; x < xF; x++)
	        {
	            current_pixel[x] = barrierColor;
	        }
	    }

	} else
	{
		cout << "coord y is out of image height." << endl;
		return;
	}
}

void PlaneBarrierDrawer::insertPlaneYZ(uint _coordX)
{
	if(_coordX >= 0 && _coordX < this->canvas.getWidth())
	{
		// set local variables
		int channels = this->canvas.rockImage[0].channels();
		uint x0 = _coordX * channels;
		uint xF = x0 + channels;
		uint y0 = 0;
		uint yF = this->canvas.getHeight();
		uint z0 = 0;
		uint zF = this->canvas.getDepth();
		uchar barrierColor = this->canvas.getRockColor();

		// draw pore
	    for (uint z = z0; z < zF; z++)
	    {
	        uchar *current_pixel;
	        for (uint y = y0; y < yF; y++)
	        {
		        current_pixel = this->canvas.rockImage[z].ptr<uchar>(y);
		        for(uint x = x0; x < xF; x++)
		        {
		        	current_pixel[x] = barrierColor;
		        }
	        }
	    }

	} else
	{
		cout << "coord x is out of image width." << endl;
		return;
	}
}