/*===
lab12-skeleton.cc

Abstract: Skeleton code for lab 12
===*/

#include "image.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// main
int main (int argc, char* argv[]) {

	// check arguments' correctness
	if (argc != 8) {
		cout << "Usage : " << argv[0]
		     << " current previous blocksize"
		     << " xblock yblock search_size output_ascii_file"
		     << endl;
	  return 1;
	}

	// load the current frame
	Image current;
	current.LoadPng ( argv[1] );

	// load the previous frame
	Image previous;
	previous.LoadPng ( argv[2] );



	// parse command line arguments
	int blockSize = atoi(argv[3]);  // the size of the block we will be comparing
	int xStart = atoi(argv[4]);     // starting horizontal pixel for the block we will compare
	int yStart = atoi(argv[5]);     // starting vertical pixel for the block we will compare
	int searchSize = atoi(argv[6]); // number of pixels up and down our search will encompass

	//DFD Image
	Image dfd_img;
	dfd_img.Resize(blockSize,blockSize);
	// initialize the 2D array holding the MSE for each displacement to have size searchSize^2
	vector<vector<double> > displacementMSE (searchSize, vector<double> (searchSize, 0) );

	cout << displacementMSE.size() <<endl;
	// fill in the displacementMSE table and print the displacement that minimizes MSE
	/*===

	Insert Lab 12 Code Here

	===*/
	/*#1 partition current frame into 16x16 subblocks
		#2 within the search range w.r.t. current block, search for MV that will result in least displacementMSE
			 between current frame and previous frame
	*/
	double prev_pix;
	double curr_pix;
	double sum;
	double mse;
	int range = 0;
	for (int i = 0; i< searchSize;i++ ){
		for (int j = 0; j< searchSize; j++){
			range = (searchSize - 1)/2;
			sum = 0;
			for (int k = 0; k < blockSize; k++){
				for(int p = 0;p<blockSize; p++){
				prev_pix = previous.Pixel(xStart +(i-range)+k,yStart +(j-range)+p);
				curr_pix = current.Pixel(xStart+k,yStart +p );
				sum += (prev_pix - curr_pix ) * (prev_pix - curr_pix);
			}
		}
			mse = sum * (double)1/(double)(blockSize * blockSize) ;
			cout << "sum" <<sum<< "mse"<<mse<<endl;
			displacementMSE[i][j] = mse;

		}
	}
double diff;
double sum_b;
ofstream out1 ("histB");
for (int x = 0; x< blockSize; x++){
	for (int y = 0; y<blockSize; y++){
		dfd_img.Pixel(x,y) = abs(current.Pixel(xStart+x,yStart+y)- previous.Pixel(xStart+x-1,yStart+y+27));
		sum_b += current.Pixel(xStart+x,yStart+y)*current.Pixel(xStart+x,yStart+y);
		out1 << dfd_img.Pixel(x,y) <<endl;
	}
}
cout<<"energy of block of current part B" <<sum_b<<endl;
out1.close();
dfd_img.SavePng("DFD_Img_partB.png");




	// save each displacement's MSE to a file
	ofstream out (argv[7]);
	if (out.fail () )
	{
		cout << "Failed to open " << argv[7] << " for writing." << endl;
		return 1;
	}
	for (int x = 0; x < searchSize; x++)
	{
		int xOffset = x - (searchSize - 1)/2;
		for (int y = 0; y < searchSize; y++)
		{
			int yOffset = y - (searchSize - 1)/2;
			out << xOffset << " " << yOffset << " " << displacementMSE[x][y] << endl;
		}
	}
	out.close ();
}
