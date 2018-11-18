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
	int row, col;
	// initialize the output interpolated image
	ComplexFFTImage outputImage;
	outputImage.Resize (512, 512);
	Complex pix;
	for ( int i = topLeftRow; i< topLeftRow+128; i++){
		for(int j = topLeftColumn; j< topLeftColumn + 128; j++){
			pix = inputImage.Pixel(i,j);
			row = i - topLeftRow;
			col = j - topLeftColumn;
			outputImage.Pixel(4*row, 4*col)= pix;
		}
	}
	//First interpolate linearly along each row between the copied pixels
	int A_idx, B_idx;
	Complex A, B;
	for (int i = 0; i< 127; i++){ //row; also excluding the boundary 4 rows
		for (int j= 0; j<127; j++){  //column; also excluding the boundary 4 columns
			A = outputImage.Pixel(4*i,4*j);
			B = outputImage.Pixel(4*i,4*j+4);
			for (int k = 1; k<4; k ++){
				outputImage.Pixel(4*i,4*j+k) = ( ( double(1)- double(k)/double(4) )*A) + ((double(k)/double(4))*B);

			}
		}
	}

	int A_row;
	int idx;
	//Second interpolate linearly along each column
	for( int i = 0; i< 512-4; i++){ //excluding the boundaries 4 rows
		for (int j = 0 ; j<512-4; j++){ //excluding the boundaries 4 columns
			idx = i%4;
			if(idx != 0){
				A_row = i-idx;
				//cout << A_row <<endl;
				A = outputImage.Pixel(A_row, j);
				B = outputImage.Pixel(A_row+4, j);
				outputImage.Pixel(i, j ) = (( double(1) - double(idx)/double(4) )*A) + (double(idx)/(double)(4)*B);

				}
			}
		}


	/*
	//Lastly, compute the boundary regions using zero order hold
	for (int i = 0; i < 128; i++){
		 pix = inputImage.Pixel(4*i,512-4 );
		 for (int j = 512-4; j < 512; j++){
			 for(int k = 1; k <4; k++){
				 	outputImage.Pixel(4*i+k,j)= pix;
			 }
		 }
	 }
	for (int i = 512-4; i<512; i++){
		for ( int j = 0; j < 128; j++){
			pix = inputImage.Pixel(512-4, j*4);
			for (int k =0 ; k<4; k++){
				outputImage.Pixel(i, 4*j+k) = pix;
			}
		}
	}
	/*===

	Insert Lab 3 code here

	Note that in this lab if you want to take the FFT of a ComplexFFTImage called image,
	you only have to call image.FourierTransform () or image.InverseFourierTransform ()

	===*/

	// save the image
	outputImage.SavePng (argv[2]);

	return 0;
}
