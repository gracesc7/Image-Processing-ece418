/*===
lab3-skeleton.cc

Abstract: Skeleton for Lab 3 parts (a), (b), and (c)
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "imagefft.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness [for parts (a) and (b) -- this needs to be changed for (c)]
	if (argc < 3)
	{
		cerr << "Usage: " << argv[0] << " in.png out.png [top] [left]" << endl;
		return 1;
	}

	// read the top row and left column that will be used [remove this for part (c)]
	int topLeftRow = atoi(argv[3]);
	int topLeftColumn = atoi(argv[4]);

	// load the input image
	ComplexFFTImage inputImage;
	inputImage.LoadPng (argv[1]);

	// initialize the output interpolated image
	ComplexFFTImage outputImage;
	//outputImage.Width()= 512;
	//outputImage.Height()=512;
	//outputImage.Resize (outputImage.Width (), outputImage.Height ());
	outputImage.Resize (512,512);

	/*===

	Insert Lab 3 code here

	Note that in this lab if you want to take the FFT of a ComplexFFTImage called image,
	you only have to call image.FourierTransform () or image.InverseFourierTransform ()

	===*/
	//Zero Order Hold (replicate pixel value from 128x128 block to corresponding 4x4 block in 512 x512 output image)
	int row, col;
	for ( int i = topLeftRow; i < (topLeftRow +128); i++){
		for (int j = topLeftColumn ; j< (topLeftColumn+128); j++){
			Complex pix;
			pix = inputImage.Pixel(i,j);
			//calculate the corresponding row, col coordinate in the resized outputimage.
			row = i - topLeftRow;
			col = j - topLeftColumn;
			for( int x = row *4; x < (row*4 +4); x++){
				for(int y = col*4; y < (col*4+4); y++){
					outputImage.Pixel(x,y)= pix;
				}
			}

		}
	}
	// save the image
	outputImage.SavePng (argv[2]);

	return 0;
}
