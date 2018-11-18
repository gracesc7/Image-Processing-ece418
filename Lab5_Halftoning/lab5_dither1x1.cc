/*===
lab5-dither1x1.cc

Abstract: Implementation of a 1x1 dithering scheme
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	// load the input image
	Image image;
	image.LoadPng ("ca_coast.png");

	double sq_sum;
	// do 1x1 dithering
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			double orig = image.Pixel(x,y);
			int& value = image.Pixel (x, y);
			value = (value < 128) ? 0 : 255;
			sq_sum += (image.Pixel(x,y) - orig) * (image.Pixel(x,y) - orig);
		}
	}
	double me = sq_sum/ (image.Width() * image.Height());
	cout <<"Mean Square Error of 1x1 dither" <<me<<endl;


	// save the image
	image.SavePng ("ca_coast_dither1x1.png");

	return 0;
}
