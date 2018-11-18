/*===
lab5-errdiff-skeleton.cc

Abstract: Skeleton code for an error diffusion scheme
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



	/*===

	You may want to set up an image (doubles as pixel values) to store
	the error at each pixel

	===*/


	//top to bottom and left to right
	ImageTemplate<double> error;
	error.Resize (image.Width (), image.Height () );

	ImageTemplate<double> outimage;
	outimage.Resize(image.Width (), image.Height () );

	// dither the image (note we must traverse in raster-scan order here)

//initialize error image with zeros.
for (int y= 0; y < image.Height (); y++)
{
	for (int x = 0; x < image.Width (); x++)
	{
		error.Pixel(y,x)  = double(0);

	}
}

// 1/16 5/16 3/16
// 7/16  X

for (int y = 0; y<image.Height(); y++){
	for (int x = 0; x<image.Width(); x++){
		double sum=0;    //sum the neghbors with weights and assign it to X in error image
		if(x>0){ //7/16;
			sum += 7.0*error.Pixel(x-1,y)/16.0;
		}

		if(x>0 && y>0){ //1/16
			sum += error.Pixel(x-1,y-1)/16.0;
		}
		if(y>0){  //5/16
			sum += 5.0*error.Pixel(x,y-1)/16.0;
		}
		if(x<image.Width()-1 && y>0){ //3/16

			sum += 3.0*error.Pixel(x+1,y-1)/16.0;
		}
		error.Pixel(x,y) = sum;
		// O = I - E;
		outimage.Pixel(x,y) = image.Pixel(x,y) - error.Pixel(x,y);
		double val = outimage.Pixel(x,y);
		double& value = outimage.Pixel(x,y);
		value = (outimage.Pixel(x,y) < 128) ? 0:255; //quantization
		//E = QO - O update the error image
		error.Pixel(x,y) = outimage.Pixel(x,y) - val;

	}
}

double sq_sum;
for (int y = 0; y<image.Height(); y++){
	for (int x = 0; x<image.Width(); x++){
		sq_sum += (image.Pixel(x,y) - outimage.Pixel(x,y)) * (image.Pixel(x,y) - outimage.Pixel(x,y));
	}
}
double me = sq_sum / (image.Height() * image.Width());
cout <<"Mean Square Error of error diffusion:" << me << endl;


	// save the image
	outimage.SavePng ("ca_coast_errdiff_scz00.png");
	return 0;
}
